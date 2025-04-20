#pragma once
#include "Light.h"


class PointLight : public Light 
{
public:
    rtx::Vector3 position;

    PointLight() : Light(), position(rtx::Vector3::Zero()) {}
    PointLight(rtx::Vector3 position) : Light(), position(position) {}
};
