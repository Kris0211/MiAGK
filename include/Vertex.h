#pragma once

#include "../RasTerX/include/Vector3.hpp"
#include "Color.h"

class Vertex {
public:
    rtx::Vector3 position;
    rtx::Vector3 normal;
    Color color;

    Vertex() = default;
    Vertex(const rtx::Vector3& position, const rtx::Vector3& normal = rtx::Vector3::Up(), 
        Color color = Color(Color::WHITE)) : position(position), normal(normal), color(color) {};

};
