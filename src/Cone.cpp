#include "../include/Cone.h"

Cone::Cone(const float radius, const float height, const int sectors, Color color) {
    float step = (360.f / static_cast<float>(sectors)) * HALF_PI;
    for (float angle = 0.0f; angle < TAU; angle += step)
    {
        rtx::Vector3 p0 = PointOnCircle(angle, radius);
        rtx::Vector3 p1 = PointOnCircle(angle + step, radius);

        Vertex v1(p1, rtx::Vector3::Up());
        Vertex v2(rtx::Vector3(0.f, height, 0.f), rtx::Vector3::Up());
        Vertex v3(p0, rtx::Vector3::Up());
        tris.emplace_back(v1, v2, v3, Color::RED, Color::GREEN, Color::BLUE);


        Vertex v4(p0, rtx::Vector3::Up());
        Vertex v5(rtx::Vector3::Zero(), rtx::Vector3::Up());
        Vertex v6(p1, rtx::Vector3::Up());
        tris.emplace_back(v4, v5, v6, Color::RED, Color::GREEN, Color::BLUE);
    }
}

rtx::Vector3 Cone::PointOnCircle(const float angle, const float radius, rtx::Vector3 center)
{
    return 
    {
        radius * std::cos(angle) + center.x,
        center.y,
        radius * std::sin(angle) + center.z 
    };
}
