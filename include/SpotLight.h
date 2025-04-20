#pragma once
#include "Light.h"

class SpotLight : public Light {

public:
    rtx::Vector3 position;
    rtx::Vector3 direction;
    float cutoff;

    SpotLight() : Light(), position(rtx::Vector3::Zero()), 
        direction(rtx::Vector3(0.f, -1.f, 0.f)), cutoff(45.f) {}
    SpotLight(rtx::Vector3 position, rtx::Vector3 direction, const float cutoff = 45.f)
        : position(position), direction(direction), cutoff(cutoff) {}
};
