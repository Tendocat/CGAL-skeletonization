#include "Skeleton.hpp"

float Skeleton::dist(const pmp::Point &p1, const pmp::Point &p2)
{
    return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2) + pow(p2[2] - p1[2], 2));
}

float Skeleton::dist_to_skeleton(const pmp::Point &p1, const pmp::SurfaceMesh &skeleton)
{
    float curr_dist, min_dist = std::numeric_limits<float>::max();

    for (auto const &v : skeleton.vertices())
    {
        if ((curr_dist = dist(p1, skeleton.position(v))) < min_dist)
            min_dist = curr_dist;
        
        // amélioration : vérifier que le distance mesurée est bien interne au maillage et ne passe pas par l'extérieur (le cas est très rare, mais peut sûrement arriver)
    }
    return min_dist;
}

/* calcul du squelette avec CGAL */
pmp::SurfaceMeshGL Skeleton::compute_skeleton(const std::string &path)
{
    // TODO ...
    return pmp::SurfaceMeshGL{};
}

/* algo de colorimétrie-évaluation du squelette */
void Skeleton::evaluate_skeleton(pmp::SurfaceMesh &mesh, const pmp::SurfaceMesh &skeleton) {
    if (mesh.n_vertices() == 0 || skeleton.n_vertices() == 0)
    {
        std::cout << "Please load mesh and skeleton" << std::endl;
        return;
    }

    float sum = 0;
    float cpt = 0;

    auto vdist = mesh.vertex_property<float>("d:dist");

    for (auto const &v : mesh.vertices())
    {
        vdist[v] = dist_to_skeleton(mesh.position(v), skeleton);
        sum += vdist[v];
        cpt++;
    }

    float mean = sum / cpt; // la moyenne est une mesure statistique comme une autre, on pourrait utiliser la médiane et même encore d'autres métriques
    float ratio = 0;

    auto vcolor = mesh.vertex_property<pmp::Color>("v:color");

    for (auto const &v : mesh.vertices())
    {
        ratio = std::min(vdist[v] / mean, 1.0f);
        vcolor[v] = (1 - ratio) * pmp::Color(1, 0, 0) + ratio * pmp::Color(1, 1, 1);
    }
}