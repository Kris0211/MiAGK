#include "../include/Rasterizer.h"
#include "../include/FileSaver.h"
#include "../RasTerX/include/MathUtils.hpp"
#include <iostream>
#include "../RasTerX/include/Matrix4.hpp"
#include "../include/VertexProcessor.h"

Rasterizer::Rasterizer(const int sizeX, const int sizeY) 
	: _colorBuffer(sizeX, sizeY) {}


void Rasterizer::Render(const std::vector<rtx::Triangle>& triangles,
	const std::vector<rtx::Matrix4>& models, Color bgColor)
{
	_colorBuffer.FillColor(bgColor.ToHex());
	_colorBuffer.FillDepth(FLT_MAX);
	for (int i = 0; i < triangles.size(); i++)
	{
		RenderTriangle(triangles[i], models[i]);
	}
}

void Rasterizer::Save(std::string fileName)
{
	FileSaver::SaveTGA(fileName, _colorBuffer.GetColorData(),
		_colorBuffer.GetSizeX(), _colorBuffer.GetSizeY());
}

void Rasterizer::RenderTriangle(rtx::Triangle triangle, const rtx::Matrix4& model, Color color)
{
	const int width = _colorBuffer.GetSizeX();
	const int height = _colorBuffer.GetSizeY();

	rtx::Matrix4 projection = VertexProcessor::SetPerspective(fov, aspect, near, far);
	rtx::Matrix4 view = VertexProcessor::SetLookAt(
		rtx::Vector3::Forward(), rtx::Vector3::Zero(), rtx::Vector3::Up());
	
	rtx::Matrix4 cam;
	cam.LoadIdentity();

	cam = cam * projection * view;

	rtx::Vector4 transformedVertexA = model * cam * rtx::Vector4(
		triangle.GetVertA().x, triangle.GetVertA().y, triangle.GetVertA().z, 1.0f);
	const int x1 = (transformedVertexA.x + 1.0f) * width * 0.5f;
	const int y1 = (transformedVertexA.y + 1.0f) * height * 0.5f;

	rtx::Vector4 transformedVertexB = model * cam * rtx::Vector4(
		triangle.GetVertB().x, triangle.GetVertB().y, triangle.GetVertB().z, 1.0f);
	const int x2 = (transformedVertexB.x + 1.0f) * width * 0.5f;
	const int y2 = (transformedVertexB.y + 1.0f) * height * 0.5f;

	rtx::Vector4 transformedVertexC = model * cam * rtx::Vector4(
		triangle.GetVertC().x, triangle.GetVertC().y, triangle.GetVertC().z, 1.0f);
	const int x3 = (transformedVertexC.x + 1.0f) * width * 0.5f;
	const int y3 = (transformedVertexC.y + 1.0f) * height * 0.5f;

	const float z1 = triangle.GetVertA().z;
	const float z2 = triangle.GetVertB().z;
	const float z3 = triangle.GetVertC().z;

	int minX = rtx::MathUtils::Min3<int>(x1, x2, x3);
	int maxX = rtx::MathUtils::Max3<int>(x1, x2, x3);
	int minY = rtx::MathUtils::Min3<int>(y1, y2, y3);
	int maxY = rtx::MathUtils::Max3<int>(y1, y2, y3);

	minX = (int)std::max(minX, (int)0);
	maxX = (int)std::min(maxX, width);
	minY = (int)std::max(minY, (int)0);
	maxY = (int)std::min(maxY, height);

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

	const bool tl1 = (dy12 < 0 || (dy12 == 0 && dx12 > 0));
	const bool tl2 = (dy23 < 0 || (dy23 == 0 && dx23 > 0));
	const bool tl3 = (dy31 < 0 || (dy31 == 0 && dx31 > 0));

	const float ud = 1.f / (dy23 * dx13 + dx32 * dy13);
	const float vd = 1.f / (dy31 * dx23 + dx13 * dy23);

	for (int screenY = minY; screenY < maxY; ++screenY) 
	{
		for (int screenX = minX; screenX < maxX; ++screenX) 
		{
			const int dxs3 = screenX - x3;
			const int dys3 = screenY - y3;

			const float edge1 = dx12 * (screenY - y1) - dy12 * (screenX - x1);
			const float edge2 = dx23 * (screenY - y2) - dy23 * (screenX - x2);
			const float edge3 = dx31 * dys3 - dy31 * dxs3;

			if ((edge1 > 0 || (edge1 >= 0 && tl1))
				&& (edge2 > 0 || (edge2 >= 0 && tl2))
				&& (edge3 > 0 || (edge3 >= 0 && tl3)))
			{

				const float barU = (dy23 * dxs3 + dx32 * dys3) * ud;
				const float barV = (dy31 * dxs3 + dx13 * dys3) * vd;
				const float barW = 1.f - barU - barV;

				const float screenDepth = _colorBuffer.GetDepthAt(screenX, screenY);
				const float currentDepth = barU * z1 + barV * z2 + barW * z3;
				if (currentDepth < screenDepth) 
				{
					rtx::Vector3 red = Color(Color::RED).ToVector();
					rtx::Vector3 green = Color(Color::GREEN).ToVector();
					rtx::Vector3 blue = Color(Color::BLUE).ToVector();

					rtx::Vector3 pixelColor = red * barU + green * barV + blue * barW;

					_colorBuffer.SetPixel(screenX, screenY, Color(pixelColor).ToHex());
					_colorBuffer.SetDepthAt(screenX, screenY, currentDepth);
				}
			}
		}
	}
}
