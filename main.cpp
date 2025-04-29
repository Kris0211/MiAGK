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

constexpr int texWidth = 128;
constexpr int texHeight = 128;

int main(int argc, char* argv[])
{
	Buffer tex1(texWidth, texHeight);
	Buffer tex2(texWidth, texHeight);

	if (!tex1.OpenImage("res/cobble.tga", texWidth, texHeight))
		return -1;

	if (!tex2.OpenImage("res/lava.tga", texWidth, texHeight))
		return -1;

	Buffer buf(imgWidth, imgHeight);
	Rasterizer rasterizer(imgWidth, imgHeight);

	// Meshes
	Cone c(0.25f, 1.f, 12);
	std::shared_ptr<Cone> cone = std::make_shared<Cone>(c);

	rtx::Matrix4 coneModel;
	coneModel.LoadIdentity();
	coneModel = coneModel * VertexProcessor::Translate({ -0.5f, 1.f, 0.f });
	coneModel = coneModel * VertexProcessor::Rotate(30.f, rtx::Vector3::Right());
	coneModel = coneModel * VertexProcessor::Rotate(-45.f, rtx::Vector3::Forward());

	Renderable coneRenderable(cone, coneModel, nullptr, true);


	SphereMesh s(0.5f, 8, 8);
	std::shared_ptr<SphereMesh> sphere = std::make_shared<SphereMesh>(s);

	rtx::Matrix4 sphereModel;
	sphereModel.LoadIdentity();
	sphereModel = sphereModel * VertexProcessor::Translate({0.f, 0.8f, 0.f});

	Renderable sphereRenderable(sphere, sphereModel, &tex1, false, false);


	SphereMesh s2(0.5f, 8, 8);
	std::shared_ptr<SphereMesh> sphere2 = std::make_shared<SphereMesh>(s2);

	rtx::Matrix4 secondSphereModel;
	secondSphereModel.LoadIdentity();
	secondSphereModel = secondSphereModel * VertexProcessor::Translate({ -0.7f, -0.4f, 0.f });

	Renderable secondSphereRenderable(sphere2, secondSphereModel, &tex1);



	SphereMesh s3(0.5f, 8, 8);
	std::shared_ptr<SphereMesh> sphere3 = std::make_shared<SphereMesh>(s3);

	rtx::Matrix4 thirdSphereModel;
	thirdSphereModel.LoadIdentity();
	thirdSphereModel = thirdSphereModel * VertexProcessor::Translate({ 0.7f, -0.4f, 0.f });

	Renderable thirdSphereRenderable(sphere3, thirdSphereModel, &tex2);

	Torus t(0.5f, 0.25f, 8, 6);
	std::shared_ptr<Torus> torus = std::make_shared<Torus>(t);

	rtx::Matrix4 torusModel;
	torusModel.LoadIdentity();
	torusModel = torusModel * VertexProcessor::Rotate(30.f, rtx::Vector3::Right());
	torusModel = torusModel * VertexProcessor::Rotate(60.f, rtx::Vector3::Forward());
	torusModel = torusModel * VertexProcessor::Translate({ 1.f, -1.5f, 2.f });

	Renderable torusRenderable(torus, torusModel, nullptr, true);


	// Lights
	PointLight pl(rtx::Vector3(0.f, 0.f, 1.f));
	DirectionalLight dl(rtx::Vector3::Right());
	//SpotLight sl({0.f, 0.7f, 2.f}, rtx::Vector3::Forward(), 15.f);

	std::shared_ptr<PointLight> pointLight = std::make_shared<PointLight>(pl);
	std::shared_ptr<DirectionalLight> dirLight = std::make_shared<DirectionalLight>(dl);
	//std::shared_ptr<SpotLight> spotLight = std::make_shared<SpotLight>(sl);


	//std::vector<Renderable> renderables = { coneRenderable, sphereRenderable, torusRenderable, secondSphereRenderable };
	std::vector<Renderable> renderables = { sphereRenderable, secondSphereRenderable, thirdSphereRenderable };
	
	//std::vector<std::shared_ptr<Light>> sceneLights = { pointLight };
	std::vector<std::shared_ptr<Light>> sceneLights = { dirLight };
	//std::vector<std::shared_ptr<Light>> sceneLights = { pointLight, dirLight };

	rasterizer.Render(renderables, sceneLights, Color(Color::GRAY));
	rasterizer.Save("image.tga");

	return 0;
}
