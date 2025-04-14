#pragma once

#include "../include/Mesh.h"

class MeshTriangle : public Mesh {
public:
    MeshTriangle();

    MeshTriangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3);
    MeshTriangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3,
        Color color1, Color color2, Color color3);

	rtx::Vector3 GetVertA() const { return vertices[0].position; }
    rtx::Vector3 GetVertB() const { return vertices[1].position; }
    rtx::Vector3 GetVertC() const { return vertices[2].position; }

};