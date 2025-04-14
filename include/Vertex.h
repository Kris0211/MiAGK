#pragma once

#include "../RasTerX/include/Vector3.hpp"

class Vertex {
public:
    rtx::Vector3 position;
    rtx::Vector3 normal;

    Vertex() = default;
    Vertex(const rtx::Vector3& position, const rtx::Vector3& normal = rtx::Vector3::Up()) :
        position(position), normal(normal) {};

};
