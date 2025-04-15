#pragma once

#include "../RasTerX/include/Vector3.hpp"
#include "Color.h"
#include "Vertex.h"

#include <vector>

class MeshTriangle
{
public:
    std::vector<Vertex> vertices;
    std::vector<rtx::Vector3> indices;
    std::vector<Color> colors;

    MeshTriangle();
    MeshTriangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3);
    MeshTriangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3,
        Color color1, Color color2, Color color3);

    rtx::Vector3 GetVertA() const { return vertices[0].position; }
    rtx::Vector3 GetVertB() const { return vertices[1].position; }
    rtx::Vector3 GetVertC() const { return vertices[2].position; }

};
