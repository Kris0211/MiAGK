#pragma once

#include "Buffer.h"
#include "../RasTerX/include/Triangle.hpp"
#include "../include/Color.h"

class Rasterizer 
{
public:
	Rasterizer(const int sizeX, const int sizeY);
	
	void Render(const std::vector<rtx::Triangle>& triangles, Color bgColor);

	void Save(std::string fileName);

private:
	Buffer _colorBuffer;

	void RenderTriangle(rtx::Triangle triangle, Color color = Color(Color::WHITE));
};