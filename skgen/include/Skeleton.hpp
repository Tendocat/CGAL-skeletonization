#pragma once

#include "pmp/SurfaceMesh.h"

class Skeleton : public pmp::SurfaceMesh {

public:
    Skeleton(const pmp::SurfaceMesh &mesh);
};