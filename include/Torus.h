#pragma once

#include "Mesh.h"
#include "MeshTriangle.h"

class Torus : public Mesh 
{
public:
    Torus(const float majorRadius, const float minorRadius,
        const int majorSegments, const int minorSegments);

private:
    rtx::Vector3 CalculateTorusPoint(const float majorRadius, const float minorRadius,
        const float majorAngle, const float minorAngle);

    rtx::Vector3 CalculateNormal(const rtx::Vector3& point, const float majorRadius, const float minorRadius);

    rtx::Vector2 TexCoords(const float majorAngle, const float minorAngle,
        const unsigned int texWidth, const unsigned int texHeight);
};
