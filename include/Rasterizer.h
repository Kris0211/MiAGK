#pragma once

#include "Buffer.h"
#include "../RasTerX/include/Triangle.hpp"

class Rasterizer 
{
public:
	Rasterizer(const int sizeX, const int sizeY);

	void Render(rtx::Triangle triangle, unsigned int bgColor, unsigned int triangleColor);

private:
	Buffer _colorBuffer;

	void RenderTriangle(rtx::Triangle triangle, unsigned int color);
};