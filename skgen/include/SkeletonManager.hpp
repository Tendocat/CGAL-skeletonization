#pragma once

#include <pmp/visualization/MeshViewer.h>
#include <pmp/SurfaceMesh.h>
#include <filesystem>

/**
 * @brief Statistical metrics used for skeleton evaluation.
 */
enum class Metrics { MEAN, MEDIAN };

/**
 * @brief This class is filled with methods for skeleton computing and analysis.
 */
class SkeletonManager
{
    private:
        /**
         * @brief Computes the minimal distance between a vertex and a skeleton mesh.
         */
        static float dist_point_skeleton(const pmp::Point &p1, const pmp::SurfaceMesh &skeleton);

    public:
        // program path
        static std::filesystem::path programPath;

        /**
         * @brief Calls CGAL program using the 'Mean Curvature Flow' algorithm.
         */
        static pmp::SurfaceMeshGL compute_skeleton(const std::string &path);

        /**
         * @brief Initializes the minimal distance of each vertex of a mesh and its skeleton mesh.
         */
        static void dist_mesh_skeleton(pmp::SurfaceMesh &mesh, const pmp::SurfaceMesh &skeleton);

        /**
         * @brief Colorizes the mesh breaking parts using the precomputed distances to the skeleton mesh.
         */
        static void evaluate_skeleton(pmp::SurfaceMesh &mesh, Metrics metric = Metrics::MEAN, float break_ratio = 1.0f);
};
