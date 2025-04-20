#pragma once

#include "../RasTerX/include/Vector3.hpp"
#include "Color.h"

class Light
{
public:
	Color ambient;
	Color diffuse;
	Color specular;
	float shininess;

	Light() : 
		ambient(0.5f, 0.3f, 0.8f), 
		diffuse(0.6f, 0.6f, 0.6f), 
		specular(0.1f, 0.1f, 0.1f),
		shininess(0.f)
	{}

	virtual ~Light() = default;
};	