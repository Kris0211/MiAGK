#pragma once

#include "Light.h"

class DirectionalLight : public Light {
public:
    rtx::Vector3 direction;

    DirectionalLight() : Light(), direction(rtx::Vector3(0.f, -1.f, 0.f).Normal()) {}
    DirectionalLight(rtx::Vector3 direction) : Light(), direction(direction) {}
};
