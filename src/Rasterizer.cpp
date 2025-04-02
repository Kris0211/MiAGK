#include "../include/Rasterizer.h"
#include "../include/FileSaver.h"
#include "../RasTerX/include/MathUtils.hpp"
#include <iostream>

Rasterizer::Rasterizer(const int sizeX, const int sizeY) 
	: _colorBuffer(sizeX, sizeY) {}

void Rasterizer::Render(const std::vector<rtx::Triangle>& triangles, Color bgColor)
{
	_colorBuffer.FillColor(bgColor.ToHex());
	for (const rtx::Triangle& t : triangles)
	{
		RenderTriangle(t);
	}
}

void Rasterizer::Save(std::string fileName)
{
	FileSaver::SaveTGA(fileName, _colorBuffer.GetColorData(),
		_colorBuffer.GetSizeX(), _colorBuffer.GetSizeY());
}

void Rasterizer::RenderTriangle(rtx::Triangle triangle, Color color)
{
	const int sizeX = _colorBuffer.GetSizeX();
	const int sizeY = _colorBuffer.GetSizeY();

	const int x1 = (triangle.GetVertA().x + 1.f) * sizeX * 0.5f;
	const int x2 = (triangle.GetVertB().x + 1.f) * sizeX * 0.5f;
	const int x3 = (triangle.GetVertC().x + 1.f) * sizeX * 0.5f;
	
	const int y1 = (triangle.GetVertA().y + 1.f) * sizeY * 0.5f;
	const int y2 = (triangle.GetVertB().y + 1.f) * sizeY * 0.5f;
	const int y3 = (triangle.GetVertC().y + 1.f) * sizeY * 0.5f;

	int minX = rtx::MathUtils::Min3<int>(x1, x2, x3);
	int maxX = rtx::MathUtils::Max3<int>(x1, x2, x3);
	int minY = rtx::MathUtils::Min3<int>(y1, y2, y3);
	int maxY = rtx::MathUtils::Max3<int>(y1, y2, y3);

	minX = (int)std::max(minX, (int)0);
	maxX = (int)std::min(maxX, sizeX);
	minY = (int)std::max(minY, (int)0);
	maxY = (int)std::min(maxY, sizeY);

	const int dx12 = x1 - x2;
	const int dx13 = x1 - x3;
	//const int dx21 = x2 - x1;
	const int dx23 = x2 - x3;
	const int dx31 = x3 - x1;
	const int dx32 = x3 - x2;

	const int dy12 = y1 - y2;
	const int dy13 = y1 - y3;
	//const int dy21 = y2 - y1;
	const int dy23 = y2 - y3;
	const int dy31 = y3 - y1;
	//const int dy32 = y3 - y2;

	const float ud = 1.f / (dy23 * dx13 + dx32 * dy13);
	const float vd = 1.f / (dy31 * dx23 + dx13 * dy23);

	for (int screenY = minY; screenY < maxY; ++screenY) 
	{
		for (int screenX = minX; screenX < maxX; ++screenX) 
		{
			const int dxs3 = screenX - x3;
			const int dys3 = screenY - y3;

			if (dx12 * (screenY - y1) - dy12 * (screenX - x1) > 0
				&& dx23 * (screenY - y2) - dy23 * (screenX - x2) > 0
				&& dx31 * (screenY - y3) - dy31 * (screenX - x3) > 0) 
			{

				float barU = (dy23 * dxs3 + dx32 * dys3) * ud;
				float barV = (dy31 * dxs3 + dx13 * dys3) * vd;
				float barW = 1.f - barU - barV;

				rtx::Vector3 red = Color(Color::RED).ToVector();
				rtx::Vector3 green = Color(Color::GREEN).ToVector();
				rtx::Vector3 blue = Color(Color::BLUE).ToVector();

				rtx::Vector3 pixelColor = red * barU + green * barV + blue * barW;

				_colorBuffer.SetPixel(screenX, screenY, Color(pixelColor).ToHex());
			}
		}
	}
}
