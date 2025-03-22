#include "../include/Rasterizer.h"
#include "../include/FileSaver.h"
#include "../RasTerX/include/MathUtils.hpp"

Rasterizer::Rasterizer(const int sizeX, const int sizeY) 
	: _colorBuffer(sizeX, sizeY) {}

void Rasterizer::Render(rtx::Triangle triangle, unsigned int bgColor, unsigned int triangleColor)
{
	_colorBuffer.FillColor(bgColor);
	RenderTriangle(triangle, triangleColor);
	FileSaver::SaveTGA("image.tga", _colorBuffer.GetColorData(),
		_colorBuffer.GetSizeX(), _colorBuffer.GetSizeY());
}

void Rasterizer::RenderTriangle(rtx::Triangle triangle, unsigned int color)
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
	const int dx23 = x2 - x3;
	const int dx31 = x3 - x1;

	const int dy12 = y1 - y2;
	const int dy23 = y2 - y3;
	const int dy31 = y3 - y1;

	for (int screenY = minY; screenY < maxY; ++screenY) 
	{
		for (int screenX = minX; screenX < maxX; ++screenX) 
		{
			if (dx12 * (screenY - y1) - dy12 * (screenX - x1) > 0
				&& dx23 * (screenY - y2) - dy23 * (screenX - x2) > 0
				&& dx31 * (screenY - y3) - dy31 * (screenX - x3) > 0) 
			{
				_colorBuffer.SetPixel(screenX, screenY, color);
			}
		}
	}
}
