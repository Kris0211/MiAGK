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
		ambient(0.4f, 0.4f, 0.4f), 
		diffuse(0.6f, 0.6f, 0.6f), 
		specular(0.1f, 0.1f, 0.1f),
		shininess(0.f)
	{}

	virtual ~Light() = default;
};	