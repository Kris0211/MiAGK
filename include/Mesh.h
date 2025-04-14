#pragma once

#include "Vertex.h"
#include "Color.h"

class Mesh {
public:
    int vSize = 3;
    int tSize = 1;

    std::vector<Color> colors;
    std::vector<Vertex> vertices{};
    std::vector<rtx::Vector3> indices{};

    Mesh() = default;
    virtual ~Mesh() = default;
};
