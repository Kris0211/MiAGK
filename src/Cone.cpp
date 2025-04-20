#include "../include/Cone.h"

Cone::Cone(const float radius, const float height, const int sectors) {
    float step = (360.f / static_cast<float>(sectors)) * HALF_PI;
    for (float angle = 0.0f; angle < TAU; angle += step)
    {
        rtx::Vector3 p0 = Mesh::PointOnCircle(angle, radius);
        rtx::Vector3 p1 = Mesh::PointOnCircle(angle + step, radius);

        rtx::Vector3 baseNormal = rtx::Vector3::Up();
        rtx::Vector3 sideNormal = (p1 - p0).Cross(rtx::Vector3(0.f, -height, 0.f)).Normal();

        Vertex v1(p1, sideNormal, Color(Color::RED));
        Vertex v2(rtx::Vector3(0.0f, height, 0.0f), baseNormal, Color(Color::GREEN));
        Vertex v3(p0, sideNormal, Color(Color::BLUE));

        Vertex v4(p0, sideNormal, Color(Color::RED));
        Vertex v5(rtx::Vector3::Zero(), -rtx::Vector3::Up(), Color(Color::GREEN));
        Vertex v6(p1, sideNormal, Color(Color::BLUE));

        triangles.emplace_back(v1, v2, v3);
        triangles.emplace_back(v4, v5, v6);
    }

    rtx::Vector3 topNormal = -rtx::Vector3::Up();
    Vertex top_vertex(rtx::Vector3(0.0f, height, 0.0f), topNormal, Color(Color::WHITE));

    vertices.push_back(top_vertex);
}
