#pragma once

#include "Mesh.h"
#include "MeshTriangle.h"

class Cone : public Mesh {
public:
    Cone(const float radius, const float height, const int sectors);

    rtx::Vector2 TexCoords(const float x, const float y, const float z,
        const float height);
};
