#include "../include/MeshTriangle.h"
#include "../RasTerX/include/Vector3.hpp"

MeshTriangle::MeshTriangle()
{
    vertices[0].position = rtx::Vector3(-0.5f, 0.f, 0.f);
    vertices[1].position = rtx::Vector3(0.f, 0.5f, 0.f);
    vertices[2].position = rtx::Vector3(0.5f, 0.f, 0.f);

    colors.push_back(Color::AZURE);
    colors.push_back(Color::AZURE);
    colors.push_back(Color::AZURE);

    indices[0] = rtx::Vector3(0, 1, 2);
}


MeshTriangle::MeshTriangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3)
{
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);

    colors.push_back(Color::AZURE);
    colors.push_back(Color::AZURE);
    colors.push_back(Color::AZURE);

    indices.push_back(rtx::Vector3(0, 1, 2));
}

MeshTriangle::MeshTriangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3,
	Color color1, Color color2, Color color3)
{
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);

    colors.push_back(color1);
    colors.push_back(color2);
    colors.push_back(color3);

    indices.push_back(rtx::Vector3(0, 1, 2));
}
