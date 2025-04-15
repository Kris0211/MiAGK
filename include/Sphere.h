#pragma once

#include "Mesh.h"
#include "MeshTriangle.h"

class Sphere : public Mesh 
{
public:
    Sphere(const float radius, const int sectors, const int stacks);
};
