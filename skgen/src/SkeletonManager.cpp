#include "SkeletonManager.hpp"
#include "util.hpp"

#include <numeric>

float SkeletonManager::dist_point_skeleton(const pmp::Point &p1, const pmp::SurfaceMesh &skeleton)
{
    float curr_dist, min_dist = std::numeric_limits<float>::max();

    for (auto const &v : skeleton.vertices())
    {
        if ((curr_dist = dist(p1, skeleton.position(v))) < min_dist)
            min_dist = curr_dist;
    }
    return min_dist;
}

std::filesystem::path SkeletonManager::programPath = std::filesystem::path();

pmp::SurfaceMeshGL SkeletonManager::compute_skeleton(const std::string &path)
{
    // path to call CGAL main program
    std::filesystem::path cgalCall = 
        SkeletonManager::programPath / "CGAL_skeletonization" / "detail_MCF_Skeleton" / "detailed_skeletonizer ";

    std::error_code ec;
    std::filesystem::path p(path);
    cgalCall.concat(std::filesystem::absolute(p,ec).string());
    
    // call CGAL program to compute the skeleton
    if(std::system(cgalCall.string().c_str()) == EXIT_FAILURE)
    {
        std::cout << "Skeleton computing failure." << std::endl;
        return pmp::SurfaceMeshGL();
    }
    
    pmp::SurfaceMeshGL ret;
    ret.read("skel.obj"); // read the computed skeleton

    std::filesystem::remove("skel.obj"); // clean the file

    return ret;
}

void SkeletonManager::dist_mesh_skeleton(pmp::SurfaceMesh &mesh, const pmp::SurfaceMesh &skeleton)
{
    if (mesh.n_vertices() == 0 || skeleton.n_vertices() == 0)
    {
        std::cout << "Please load mesh and skeleton" << std::endl;
        return;
    }

    auto vdist = mesh.vertex_property<float>("v:dist");

    for (auto const &v : mesh.vertices())
        vdist[v] = dist_point_skeleton(mesh.position(v), skeleton);
    

    // high curvature is troublesome in many case

    auto curvature = pmp::SurfaceCurvature{mesh};
    curvature.analyze();
    auto vcurv = mesh.vertex_property<float>("curv:min");

    for (auto const &v : mesh.vertices())
    {
        if (vcurv[v] > 100)
        {
            vdist[v] = 0;
            for(auto const &around: mesh.vertices(v))
                vdist[around] = 0;
        }
    }
}

void SkeletonManager::evaluate_skeleton(pmp::SurfaceMesh &mesh, Metrics metric, float break_threshold)
{
    if (mesh.n_vertices() == 0)
        return;

    size_t size = mesh.n_vertices();

    float threshold = 0;
    auto vdist = mesh.vertex_property<float>("v:dist");

    if (metric == Metrics::MEAN)
    {
        for (auto const &v : mesh.vertices())
            threshold += vdist[v];

        threshold = (threshold / size) * break_threshold;
    }
    else if (metric == Metrics::MEDIAN)
    {
        auto vList = std::vector<float>{};
        for (auto const &v : mesh.vertices())
            vList.push_back(vdist[v]);

        nth_element(vList.begin(), vList.begin()+vList.size()/2, vList.end());
        threshold = vList[vList.size()/2] * break_threshold;
    }

    float ratio = 0;
    auto vcolor = mesh.vertex_property<pmp::Color>("v:color");

    for (auto const &v : mesh.vertices())
    {
        ratio = std::min(vdist[v] / threshold, 1.0f);
        vcolor[v] = (1 - ratio) * pmp::Color(2, 0, 0) + ratio * pmp::Color(1, 1, 1);
    }
}
