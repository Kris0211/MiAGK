#pragma once

#include "Mesh.h"
#include "MeshTriangle.h"

class SphereMesh : public Mesh 
{
public:
    SphereMesh(const float radius, const int sectors, const int stacks);
};
