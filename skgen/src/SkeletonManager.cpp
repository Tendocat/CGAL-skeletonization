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
        SkeletonManager::programPath / "CGAL_skeletonization" / "direct_MCF_Skeleton" / "direct_skeletonizer ";

    std::error_code ec;
    std::filesystem::path p(path);
    cgalCall.concat(std::filesystem::absolute(p,ec).string());
    
    auto ext = p.extension();
    std::cout << ext << std::endl;
    std::cout << cgalCall << std::endl;
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
}

void SkeletonManager::evaluate_skeleton(pmp::SurfaceMesh &mesh, Metrics metric, float break_threshold)
{
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
        // TODO : compute median according to 'break_threshold' ...
    }

    float ratio = 0;
    auto vcolor = mesh.vertex_property<pmp::Color>("v:color");

    for (auto const &v : mesh.vertices())
    {
        ratio = std::min(vdist[v] / threshold, 1.0f);
        vcolor[v] = (1 - ratio) * pmp::Color(1, 0, 0) + ratio * pmp::Color(1, 1, 1);
    }
}
