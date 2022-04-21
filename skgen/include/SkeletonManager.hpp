#pragma once

#include <pmp/visualization/MeshViewer.h>
#include <pmp/SurfaceMesh.h>

/**
 * @brief ...
 */
enum class Metrics { MEAN, MEDIAN };

/**
 * @brief ...
 */
class SkeletonManager
{
    private:
        /**
         * @brief ...
         */
        static float dist_point_skeleton(const pmp::Point &p1, const pmp::SurfaceMesh &skeleton);

    public:
        /**
         * @brief ...
         */
        static pmp::SurfaceMeshGL compute_skeleton(const std::string &path);

        /**
         * @brief ...
         */
        static void dist_mesh_skeleton(pmp::SurfaceMesh &mesh, const pmp::SurfaceMesh &skeleton);

        /**
         * @brief ...
         */
        static void evaluate_skeleton(pmp::SurfaceMesh &mesh, Metrics metric = Metrics::MEAN, float break_ratio = 1.0f);
};
