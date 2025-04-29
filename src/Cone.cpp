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
        Vertex v2(rtx::Vector3(0.0f, height, 0.0f), baseNormal, Color(Color::RED));
        Vertex v3(p0, sideNormal, Color(Color::RED));

        Vertex v4(p0, sideNormal, Color(Color::RED));
        Vertex v5(rtx::Vector3::Zero(), -rtx::Vector3::Up(), Color(Color::RED));
        Vertex v6(p1, sideNormal, Color(Color::RED));

        triangles.emplace_back(v1, v2, v3,
            TexCoords(v1.position.x, v1.position.y, v1.position.z, height),
            TexCoords(v2.position.x, v2.position.y, v2.position.z, height),
            TexCoords(v3.position.x, v3.position.y, v3.position.z, height));
        triangles.emplace_back(v4, v5, v6,
            TexCoords(v4.position.x, v4.position.y, v4.position.z, height),
            TexCoords(v5.position.x, v5.position.y, v5.position.z, height),
            TexCoords(v6.position.x, v6.position.y, v6.position.z, height));
    }

    rtx::Vector3 topNormal = -rtx::Vector3::Up();
    Vertex top_vertex(rtx::Vector3(0.0f, height, 0.0f), topNormal, Color(Color::WHITE));

    vertices.push_back(top_vertex);
}

rtx::Vector2 Cone::TexCoords(const float x, const float y, const float z, const float height)
{
    const float phi = atan2f(z, x);
    const float theta = acosf(y / sqrt(x * x + y * y + z * z));

    const float u = phi / TAU + 0.5f;
    const float v = theta / PI;

    return { u,v };
}
