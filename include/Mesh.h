#pragma once

#include "Vertex.h"
#include "Color.h"
#include "MeshTriangle.h"

class Mesh 
{
public:
    int vSize = 3;
    int tSize = 1;

    std::vector<Color> colors;

    std::vector<MeshTriangle> triangles;
    std::vector<Vertex> vertices;
    std::vector<rtx::Vector3> indices;

    Mesh() = default;
    virtual ~Mesh() = default;

    static rtx::Vector3 PointOnCircle(const float angle, const float radius,
        rtx::Vector3 center = rtx::Vector3::Zero());
};
