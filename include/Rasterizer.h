#pragma once

#include "Buffer.h"
#include "../RasTerX/include/Triangle.hpp"
#include "../include/Color.h"
#include "../RasTerX/include/Matrix4.hpp"
#include "Mesh.h"
#include "Cone.h"

#include <memory>

class Rasterizer 
{
public:
	Rasterizer(const int sizeX, const int sizeY);

	void SetFov(const float fov) { this->fov = fov; }
	void SetAspectRatio(const float aspect) { this->aspect = aspect; }
	
	void Render(const std::vector<std::shared_ptr<Mesh>>& meshes, const rtx::Matrix4& model, Color bgColor);

	void Save(std::string fileName);

private:
	Buffer _colorBuffer;

	float fov = 120.f;
	float aspect = 1.f;
	float near = 0.01f;
	float far = 100.f;

	void RenderMesh(std::shared_ptr<Mesh> mesh, const rtx::Matrix4& model);

	void RenderTriangle(const MeshTriangle& triangle, const rtx::Matrix4& model, Color color = Color(Color::WHITE));
};