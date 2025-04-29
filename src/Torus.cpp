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

            Vertex v1 = { p1, CalculateNormal(p1, majorRadius, minorRadius)};
            Vertex v2 = { p2, CalculateNormal(p2, majorRadius, minorRadius)};
            Vertex v3 = { p3, CalculateNormal(p3, majorRadius, minorRadius)};
            Vertex v4 = { p4, CalculateNormal(p4, majorRadius, minorRadius)};

            const unsigned int texWidth = 1;
            const unsigned int texHeight = 1;


            rtx::Vector2 t1 = TexCoords(majorAngle1, minorAngle1, texWidth, texHeight);
            rtx::Vector2 t2 = TexCoords(majorAngle1, minorAngle2, texWidth, texHeight);
            rtx::Vector2 t3 = TexCoords(majorAngle2, minorAngle2, texWidth, texHeight);
            rtx::Vector2 t4 = TexCoords(majorAngle2, minorAngle1, texWidth, texHeight);

            triangles.emplace_back(v2, v1, v3, t2, t1, t3);
            triangles.emplace_back(v3, v1, v4, t3, t1, t4);
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
    return {
        point.x / norm,
        point.y / norm,
        point.z / minorRadius
    };
}

rtx::Vector2 Torus::TexCoords(const float majorAngle, const float minorAngle, const unsigned int texWidth, const unsigned int texHeight)
{
    float u = majorAngle / TAU;
    float v = minorAngle / TAU;

    u /= texWidth;
    v /= texHeight;

    return { u, v };
};
