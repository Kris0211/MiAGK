#include "../include/Sphere.h"

Sphere::Sphere(const float radius, const int sectors, const int stacks)
{
    float sectorStep = TAU / sectors;
    float stackStep = PI / stacks;

    for (int i = 0; i < stacks; ++i) {
        float stackAngle1 = PI / 2 - i * stackStep;
        float stackAngle2 = PI / 2 - (i + 1) * stackStep;

        float y1 = radius * sinf(stackAngle1);
        float y2 = radius * sinf(stackAngle2);

        float r1 = radius * cosf(stackAngle1);
        float r2 = radius * cosf(stackAngle2);

        for (int k = 0; k < sectors; ++k)
        {
            float sectorAngle1 = k * sectorStep;
            float sectorAngle2 = (k + 1) * sectorStep;

            rtx::Vector3 p1(r1 * cosf(sectorAngle1), y1, r1 * sinf(sectorAngle1));
            rtx::Vector3 p2(r2 * cosf(sectorAngle1), y2, r2 * sinf(sectorAngle1));
            rtx::Vector3 p3(r2 * cosf(sectorAngle2), y2, r2 * sinf(sectorAngle2));
            rtx::Vector3 p4(r1 * cosf(sectorAngle2), y1, r1 * sinf(sectorAngle2));

            rtx::Vector3 n1 = p1.Normal();
            rtx::Vector3 n2 = p2.Normal();
            rtx::Vector3 n3 = p3.Normal();
            rtx::Vector3 n4 = p4.Normal();

            if (i == 0)
            {
                rtx::Vector3 top{ 0.0f, radius, 0.0f };
                triangles.emplace_back(
                    Vertex(top, top.Normal()),
                    Vertex(p2, n2),
                    Vertex(p3, n3),
                    Color::RED, Color::GREEN, Color::BLUE
                );
            }
            else if (i == (stacks - 1))
            {
                rtx::Vector3 bot{ 0.0f, -radius, 0.0f };
                triangles.emplace_back(
                    Vertex(p2, n2),
                    Vertex(bot, bot.Normal()),
                    Vertex(p1, n1),
                    Color::RED, Color::GREEN, Color::BLUE
                );
            }
            else
            {
                triangles.emplace_back(
                    Vertex(p1, n1),
                    Vertex(p2, n2),
                    Vertex(p3, n3),
                    Color::RED, Color::GREEN, Color::BLUE
                );
                triangles.emplace_back(
                    Vertex(p1, n1),
                    Vertex(p3, n3),
                    Vertex(p4, n4),
                    Color::RED, Color::GREEN, Color::BLUE
                );
            }
        }
    }
}
