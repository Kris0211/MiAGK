#include "../include/Mesh.h"

rtx::Vector3 Mesh::PointOnCircle(const float angle, const float radius, rtx::Vector3 center)
{
    return
    {
        radius * std::cos(angle) + center.x,
        center.y,
        radius * std::sin(angle) + center.z
    };
}
