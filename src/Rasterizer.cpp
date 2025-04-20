#include "../include/Rasterizer.h"
#include "../include/FileSaver.h"
#include "../RasTerX/include/MathUtils.hpp"
#include <iostream>
#include "../RasTerX/include/Matrix4.hpp"
#include "../include/VertexProcessor.h"
#include "../include/MeshTriangle.h"
#include "../include/PointLight.h"
#include "../include/DirectionalLight.h"
#include "../include/SpotLight.h"

Rasterizer::Rasterizer(const int sizeX, const int sizeY) 
	: _colorBuffer(sizeX, sizeY) {}


void Rasterizer::Render(const std::vector<std::shared_ptr<Mesh>>& meshes, 
	const std::vector<rtx::Matrix4>& models, const std::vector<std::shared_ptr<Light>>& lights, Color bgColor)
{
	_colorBuffer.FillColor(bgColor.ToHex());
	_colorBuffer.FillDepth(FLT_MAX);

	for (int i = 0; i < meshes.size(); i++)
	{
		RenderMesh(meshes[i], models[i], lights);
	}
}

void Rasterizer::Save(std::string fileName)
{
	FileSaver::SaveTGA(fileName, _colorBuffer.GetColorData(),
		_colorBuffer.GetSizeX(), _colorBuffer.GetSizeY());
}

void Rasterizer::RenderMesh(std::shared_ptr<Mesh> mesh, const rtx::Matrix4& model, 
	const std::vector<std::shared_ptr<Light>>& lights)
{
	for (auto& triangle : mesh->triangles)
	{
		MeshTriangle mTriangle = triangle;
		
		CalculateLighting(mTriangle.vertices[0], lights);
		CalculateLighting(mTriangle.vertices[1], lights);
		CalculateLighting(mTriangle.vertices[2], lights);

		RenderTriangle(mTriangle, model, lights);
	}
}

void Rasterizer::RenderTriangle(const MeshTriangle& triangle, const rtx::Matrix4& model, 
	const std::vector<std::shared_ptr<Light>>& lights, Color color)
{
	const int width = _colorBuffer.GetSizeX();
	const int height = _colorBuffer.GetSizeY();

	rtx::Matrix4 projection = VertexProcessor::SetPerspective(fov, aspect, near, far);
	rtx::Matrix4 view = VertexProcessor::SetLookAt(
		rtx::Vector3::Forward(), rtx::Vector3::Zero(), rtx::Vector3::Up()
	);
	
	rtx::Matrix4 mvp = projection * view * model;

	rtx::Vector4 transformedVertexA = mvp * rtx::Vector4(
		triangle.GetVertA().x, triangle.GetVertA().y, triangle.GetVertA().z, 1.0f);
	const int x1 = (transformedVertexA.x + 1.0f) * width * 0.5f;
	const int y1 = (transformedVertexA.y + 1.0f) * height * 0.5f;

	rtx::Vector4 transformedVertexB = mvp * rtx::Vector4(
		triangle.GetVertB().x, triangle.GetVertB().y, triangle.GetVertB().z, 1.0f);
	const int x2 = (transformedVertexB.x + 1.0f) * width * 0.5f;
	const int y2 = (transformedVertexB.y + 1.0f) * height * 0.5f;

	rtx::Vector4 transformedVertexC = mvp * rtx::Vector4(
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
	const int dx23 = x2 - x3;
	const int dx31 = x3 - x1;
	const int dx32 = x3 - x2;

	const int dy12 = y1 - y2;
	const int dy13 = y1 - y3;
	const int dy23 = y2 - y3;
	const int dy31 = y3 - y1;

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
					rtx::Vector3 c0 = triangle.vertices[0].color.ToVector();
					rtx::Vector3 c1 = triangle.vertices[1].color.ToVector();
					rtx::Vector3 c2 = triangle.vertices[2].color.ToVector();

					rtx::Vector3 pixelColor = c0 * barU + c1 * barV + c2 * barW;

					_colorBuffer.SetPixel(screenX, screenY, Color(pixelColor).ToHex());
					_colorBuffer.SetDepthAt(screenX, screenY, currentDepth);
				}
			}
		}
	}
}

void Rasterizer::CalculateLighting(Vertex& vertex, const std::vector<std::shared_ptr<Light>>& lights)
{
	rtx::Vector3 objectColor = Color(vertex.color).ToVector();
	rtx::Vector3 cameraPosition = rtx::Vector3::Zero();
	rtx::Vector3 result = rtx::Vector3::Zero();

	for (const auto& light : lights)
	{
		rtx::Vector3 ambient;
		rtx::Vector3 diffuse;
		rtx::Vector3 specular;
		rtx::Vector3 lightDir;
		float attenuation = 1.f; // no attenuation

		rtx::Vector3 ambientLight = Color(light->ambient).ToVector();
		rtx::Vector3 diffuseLight = Color(light->diffuse).ToVector();
		rtx::Vector3 specularLight = Color(light->specular).ToVector();
		const float shininess = light->shininess;

		if (auto pointLight = std::dynamic_pointer_cast<PointLight>(light))
		{
			rtx::Vector3 lightToVertex = vertex.position - pointLight->position;
			const float distance = lightToVertex.Length();
			lightDir = lightToVertex * (-1.f / distance);

			// using simplified attenuation
			attenuation = 1.f / (1.f + 0.09f * distance + 0.032f * distance * distance);
		}
		else if (auto dirLight = std::dynamic_pointer_cast<DirectionalLight>(light))
		{
			lightDir = -(dirLight->direction).Normal();
		}
		else if (auto spotLight = std::dynamic_pointer_cast<SpotLight>(light))
		{
			rtx::Vector3 lightToVertex = vertex.position - spotLight->position;
			const float distance = lightToVertex.Length();
			lightDir = lightToVertex * (-1.f / distance);

			const float cosAngle = lightDir.Dot(spotLight->direction.Normal());
			const float cosCutoff = std::cos(spotLight->cutoff * PI / 180.f);

			if (cosAngle < cosCutoff)
				continue;

			const float spotEffect = std::pow(std::max(cosAngle, 0.f), 8.f);

			// using simplified attenuation
			attenuation = spotEffect / (1.f + 0.09f * distance + 0.032f * distance * distance);
		}

		ambient = ambientLight * objectColor;

		const float diff = std::max(vertex.normal.Dot(lightDir), 0.f);
		diffuse = diffuseLight * objectColor * diff;

		rtx::Vector3 viewDir = (cameraPosition - vertex.position).Normal();
		rtx::Vector3 reflectDir = vertex.normal * (2.f * vertex.normal.Dot(lightDir)) - lightDir;
		
		const float spec = std::pow(std::max(viewDir.Dot(reflectDir), 0.f), shininess);
		specular = specularLight * spec;

		result = result + (ambient + diffuse + specular) * attenuation;
	}

	result.x = rtx::MathUtils::Clamp(result.x, 0.f, 1.f);
	result.y = rtx::MathUtils::Clamp(result.y, 0.f, 1.f);
	result.z = rtx::MathUtils::Clamp(result.z, 0.f, 1.f);
	
	vertex.color = Color(result).ToHex();
}