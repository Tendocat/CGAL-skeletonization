#pragma once

#include <pmp/visualization/MeshViewer.h>
#include "pmp/SurfaceMesh.h"

class Skeleton {
private:
    /*  */
    static float dist(const pmp::Point &p1, const pmp::Point &p2);

    /*  */
    static float dist_to_skeleton(const pmp::Point &p1, const pmp::SurfaceMesh &skeleton);

public:
    /*  */
    static pmp::SurfaceMeshGL compute_skeleton(const std::string &path);

    /*  */
    static void evaluate_skeleton(pmp::SurfaceMesh &mesh, const pmp::SurfaceMesh &skeleton);
};