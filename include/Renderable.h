#pragma once

#include "../RasTerX/include/Matrix4.hpp"
#include "Mesh.h"
#include <memory>

struct Renderable
{
    Buffer* texture;
    rtx::Matrix4 model;
    std::shared_ptr<Mesh> mesh;
    bool usePixelLighting;
    bool isLit;

    Renderable(const std::shared_ptr<Mesh>& mesh, const rtx::Matrix4& model, 
        Buffer* texture = nullptr, bool usePixelLighting = true, bool isLit = true) : 
            texture(texture), 
            model(model), 
            mesh(mesh), 
            usePixelLighting(usePixelLighting), 
            isLit(isLit)
    {}
};
