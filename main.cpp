#include "include/Buffer.h"
#include "include/FileSaver.h"
#include "include/Rasterizer.h"
#include "include/Color.h"
#include "include/VertexProcessor.h"
#include "include/SphereMesh.h"
#include "include/Torus.h"
#include "include/Light.h"
#include "include/PointLight.h"
#include "include/DirectionalLight.h"
#include "include/SpotLight.h"

constexpr int imgWidth = 512;
constexpr int imgHeight = 512;

int main(int argc, char* argv[])
{
	Buffer buf(imgWidth, imgHeight);
	Rasterizer rasterizer(imgWidth, imgHeight);

	// Meshes

	Cone c(0.25f, 1.f, 12);
	std::shared_ptr<Cone> cone = std::make_shared<Cone>(c);

	rtx::Matrix4 coneModel;
	coneModel.LoadIdentity();
	coneModel = coneModel * VertexProcessor::Rotate(30.f, rtx::Vector3::Right());
	coneModel = coneModel * VertexProcessor::Rotate(-45.f, rtx::Vector3::Forward());
	coneModel = coneModel * VertexProcessor::Translate({ -0.5f, 1.f, 0.f });

	SphereMesh s(0.5f, 8, 8);
	std::shared_ptr<SphereMesh> sphere = std::make_shared<SphereMesh>(s);

	rtx::Matrix4 sphereModel;
	sphereModel.LoadIdentity();
	sphereModel = sphereModel * VertexProcessor::Translate({ 0.f, 1.f, 0.f });


	Torus t(0.5f, 0.25f, 8, 6);
	std::shared_ptr<Torus> torus = std::make_shared<Torus>(t);

	rtx::Matrix4 torusModel;
	torusModel.LoadIdentity();
	torusModel = torusModel * VertexProcessor::Rotate(30.f, rtx::Vector3::Right());
	torusModel = torusModel * VertexProcessor::Rotate(60.f, rtx::Vector3::Forward());
	torusModel = torusModel * VertexProcessor::Translate({ 1.f, -0.5f, 0.f });

	// Lights

	PointLight pl;
	DirectionalLight dl;
	SpotLight sl;

	std::shared_ptr<PointLight> pointLight = std::make_shared<PointLight>(pl);
	std::shared_ptr<DirectionalLight> dirLight = std::make_shared<DirectionalLight>(dl);
	std::shared_ptr<SpotLight> spotLight = std::make_shared<SpotLight>(sl);

	std::vector<std::shared_ptr<Mesh>> meshes = { cone, sphere, torus };
	std::vector<rtx::Matrix4> models = { coneModel, sphereModel, torusModel };
	std::vector<std::shared_ptr<Light>> sceneLights = { pointLight, dirLight, spotLight };

	rasterizer.Render(meshes, models, sceneLights, Color(Color::GRAY));
	rasterizer.Save("image.tga");

	return 0;
}
