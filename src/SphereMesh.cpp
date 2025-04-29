#include "../include/SphereMesh.h"
#include "../RasTerX/include/MathUtils.hpp"

SphereMesh::SphereMesh(const float radius, const int sectors, const int stacks)
{
    r = radius;
    for (int i = 0; i < sectors; ++i) 
    {
        for (int k = 0; k < stacks; ++k) 
        {
            const float theta1 = static_cast<float>(i) * PI / sectors;
            const float theta2 = static_cast<float>(i + 1) * PI / sectors;
            const float phi1 = static_cast<float>(k) * TAU / stacks;
            const float phi2 = static_cast<float>(k + 1) * TAU / stacks;

            rtx::Vector3 p1 = CalculateSpherePoint(theta1, phi1);
            rtx::Vector3 p2 = CalculateSpherePoint(theta2, phi1);
            rtx::Vector3 p3 = CalculateSpherePoint(theta2, phi2);
            rtx::Vector3 p4 = CalculateSpherePoint(theta1, phi2);

            Vertex v1(p1, p1.Normal());
            Vertex v2(p2, p2.Normal());
            Vertex v3(p3, p3.Normal());
            Vertex v4(p4, p4.Normal());

            const unsigned int textureWidth = 1;
            const unsigned int textureHeight = 1;

            rtx::Vector2 t1 = TexCoords(theta1, phi1, textureWidth, textureHeight);
            rtx::Vector2 t2 = TexCoords(theta2, phi1, textureWidth, textureHeight);
            rtx::Vector2 t3 = TexCoords(theta2, phi2, textureWidth, textureHeight);
            rtx::Vector2 t4 = TexCoords(theta1, phi2, textureWidth, textureHeight);

            vertices.push_back(v1);
            vertices.push_back(v2);
            vertices.push_back(v3);
            vertices.push_back(v4);

            triangles.emplace_back(v1, v2, v3, t1, t2, t3);
            triangles.emplace_back(v1, v3, v4, t1, t3, t4);
        }
    }
}

rtx::Vector2 SphereMesh::TexCoords(const float theta, const float phi, const unsigned int texWidth, const unsigned int texHeight)
{
    float u = phi / TAU;
    float v = theta / PI;

    u /= texWidth;
    v /= texHeight;

    return { u, v };
}

void SphereMesh::CalculateTextures()
{
    for (int i = 0; i < vertices.size(); i++) 
    {
        float theta = std::acos(vertices[i].position.y / r);
        float phi = std::atan2(vertices[i].position.z, vertices[i].position.x);

        if (phi < 0)
        { 
            phi += TAU;
        }
        
        theta /= PI;

        const float u = phi / TAU;
        const float v = 1 - theta;

        tex.push_back(rtx::Vector2(u, v));
    }
}

rtx::Vector3 SphereMesh::CalculateSpherePoint(const float theta, const float phi)
{
    return 
    {
        r * sin(theta) * cos(phi),
        r * sin(theta) * sin(phi),
        r * cos(theta)
    };
}
