#include "include/Buffer.h"
#include "include/FileSaver.h"
#include "include/Rasterizer.h"
#include "include/Color.h"
#include "include/VertexProcessor.h"
#include "include/SphereMesh.h"
#include "include/Torus.h"

constexpr int imgWidth = 512;
constexpr int imgHeight = 512;

int main(int argc, char* argv[])
{
	Buffer buf(imgWidth, imgHeight);
	Rasterizer rasterizer(imgWidth, imgHeight);

	Vertex v1(rtx::Vector3(0.9f, -0.5f, -1.0f));
	Vertex v2(rtx::Vector3(0.0f, -0.5f, -1.0f));
	Vertex v3(rtx::Vector3(0.0f, 0.5f, 0.0f));

	//MeshTriangle t(v1, v2, v3, Color::RED, Color::GREEN, Color::BLUE);
	//std::shared_ptr<MeshTriangle> triangle = std::make_shared<MeshTriangle>(t);

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

	std::vector<std::shared_ptr<Mesh>> meshes = { cone, sphere, torus };
	std::vector<rtx::Matrix4> models = { coneModel, sphereModel, torusModel };

	rasterizer.Render(meshes, models, Color(Color::GRAY));
	rasterizer.Save("image.tga");

	return 0;
}
