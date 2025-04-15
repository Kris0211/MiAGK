#include "../include/Torus.h"

Torus::Torus(const float majorRadius, const float minorRadius, 
	const int majorSegments, const int minorSegments)
{
    const float majorStep = TAU / majorSegments;
    const float minorStep = TAU / minorSegments;

    for (int i = 0; i < majorSegments; ++i) 
    {
        for (int k = 0; k < minorSegments; ++k) 
        {
            const float majorAngle1 = i * majorStep;
            const float majorAngle2 = (i + 1) * majorStep;
            const float minorAngle1 = k * minorStep;
            const float minorAngle2 = (k + 1) * minorStep;

            rtx::Vector3 p1 = CalculateTorusPoint(majorRadius, minorRadius, majorAngle1, minorAngle1);
            rtx::Vector3 p2 = CalculateTorusPoint(majorRadius, minorRadius, majorAngle1, minorAngle2);
            rtx::Vector3 p3 = CalculateTorusPoint(majorRadius, minorRadius, majorAngle2, minorAngle2);
            rtx::Vector3 p4 = CalculateTorusPoint(majorRadius, minorRadius, majorAngle2, minorAngle1);

            Vertex v1 = { p1, CalculateNormal(p1, majorRadius, minorRadius) };
            Vertex v2 = { p2, CalculateNormal(p2, majorRadius, minorRadius) };
            Vertex v3 = { p3, CalculateNormal(p3, majorRadius, minorRadius) };
            Vertex v4 = { p4, CalculateNormal(p4, majorRadius, minorRadius) };

            triangles.emplace_back(v1, v2, v3);
            triangles.emplace_back(v1, v3, v4);
        }
    }
}

rtx::Vector3 Torus::CalculateTorusPoint(const float majorRadius, const float minorRadius,
    const float majorAngle, const float minorAngle)
{
    return
    {
        (majorRadius + minorRadius * std::cos(minorAngle)) * std::cos(majorAngle),
        (majorRadius + minorRadius * std::cos(minorAngle)) * std::sin(majorAngle),
        minorRadius * std::sin(minorAngle)
    };
}

rtx::Vector3 Torus::CalculateNormal(const rtx::Vector3& point, 
    const float majorRadius, const float minorRadius)
{
    const float norm = std::sqrt(point.x * point.x + point.y * point.y);
    return
    {
        (point.x * majorRadius) / norm,
        (point.y * majorRadius) / norm,
        (point.z * minorRadius) / norm
    };
}
