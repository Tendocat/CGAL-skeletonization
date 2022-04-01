#pragma once

#include "Skeleton.hpp"

class SkeletonManager {
private:
    // original mesh
    pmp::SurfaceMesh mesh_;

    // mesh's sekeleton
    Skeleton skeleton_;

    // printer nozzle radius (the minimal radius of the mesh)
    float nozzleRadius_;

    // enables hardness check
    bool hardnessCheck_;

    // enables interlacing check
    bool interlacingCheck_;

public:
    SkeletonManager();
    SkeletonManager(pmp::SurfaceMesh &mesh);
    SkeletonManager(pmp::SurfaceMesh &mesh, float nozzleRadius);

    const pmp::SurfaceMesh getSkeletonMesh() const;

    void setNozzleRadius(float nozzleRadius);
    void setMesh(pmp::SurfaceMesh &mesh);

    // check the local minimal radius of the printed mesh
    void hardnessCheck();

    // check if printed mesh has interlaced part
    void interlacingCheck();

    // clear mesh properties and color
    void cleanMesh();
};