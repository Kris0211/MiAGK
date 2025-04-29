#pragma once

#include "Mesh.h"
#include "MeshTriangle.h"

class SphereMesh : public Mesh 
{
public:
    SphereMesh(const float radius, const int sectors, const int stacks);

    rtx::Vector2 TexCoords(const float theta, const float phi,
        const unsigned int texWidth, const unsigned int texHeight);

    void CalculateTextures();

private:
    float r;

    rtx::Vector3 CalculateSpherePoint(const float theta, const float phi);
};
