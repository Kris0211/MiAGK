#pragma once

#include "Mesh.h"
#include "MeshTriangle.h"

class Cone : public Mesh {
public:
    std::vector<MeshTriangle> tris;

    Cone(const float radius, const float height, const int sectors, Color color);

    static rtx::Vector3 PointOnCircle(const float angle, const float radius, 
        rtx::Vector3 center = rtx::Vector3::Zero());
};
