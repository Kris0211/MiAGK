#pragma once

#include "Buffer.h"
#include "../RasTerX/include/Triangle.hpp"
#include "../include/Color.h"
#include "../RasTerX/include/Matrix4.hpp"
#include "Mesh.h"
#include "Cone.h"
#include "Light.h"

#include <memory>
#include "Renderable.h"

class Rasterizer 
{
public:
	Rasterizer(const int sizeX, const int sizeY);

	void SetFov(const float fov) { this->fov = fov; }
	void SetAspectRatio(const float aspect) { this->aspect = aspect; }
	
	void Render(const std::vector<Renderable>& renderables,
		const std::vector<std::shared_ptr<Light>>& lights, Color bgColor);

	void Save(std::string fileName);

private:
	Buffer _colorBuffer;

	float fov = 120.f;
	float aspect = 1.f;
	float near = 0.01f;
	float far = 100.f;

	void RenderMesh(std::shared_ptr<Mesh> mesh, const rtx::Matrix4& model,
		const std::vector<std::shared_ptr<Light>>& lights, Buffer* texture = nullptr,
		bool usePixelLighting = true, bool isLit = true);

	void RenderTriangle(const MeshTriangle& triangle, const rtx::Matrix4& model,
		const std::vector<std::shared_ptr<Light>>& lights, Buffer* texture = nullptr,
		bool usePixelLighting = true, bool isLit = true, Color fallbackColor = Color(Color::WHITE));

	void CalculateVertexLighting(Vertex& ref_Vertex, const rtx::Matrix4& model, 
		const std::vector<std::shared_ptr<Light>>& lights);

	rtx::Vector3 CalculatePixelLighting(const rtx::Vector3& pixelPosition,
		const rtx::Vector3& pixelNormal, const rtx::Vector3& objectColor,
		const std::vector<std::shared_ptr<Light>>& lights);

	rtx::Vector3 InterpolateColor(const MeshTriangle& triangle, float barU, float barV, float barW);
};
