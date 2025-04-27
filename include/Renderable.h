#pragma once

#include "../RasTerX/include/Matrix4.hpp"
#include "Mesh.h"
#include <memory>

struct Renderable
{
    std::shared_ptr<Mesh> mesh;
    rtx::Matrix4 model;
    bool usePixelLighting;

    Renderable(const std::shared_ptr<Mesh>& mesh, const rtx::Matrix4& model, bool usePixelLighting = false)
        : mesh(mesh), model(model), usePixelLighting(usePixelLighting) 
    {}
};
