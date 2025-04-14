#include "include/Buffer.h"
#include "include/FileSaver.h"
#include "include/Rasterizer.h"
#include "include/Color.h"
#include "include/VertexProcessor.h"

constexpr int imgWidth = 512;
constexpr int imgHeight = 512;

int main(int argc, char* argv[])
{
	Buffer buf(imgWidth, imgHeight);
	Rasterizer rasterizer(imgWidth, imgHeight);

	Vertex v1(rtx::Vector3(0.9f, -0.5f, -1.0f));
	Vertex v2(rtx::Vector3(0.0f, -0.5f, -1.0f));
	Vertex v3(rtx::Vector3(0.0f, 0.5f, 0.0f));

	MeshTriangle t(v1, v2, v3, Color::RED, Color::GREEN, Color::BLUE);
	std::shared_ptr<MeshTriangle> triangle = std::make_shared<MeshTriangle>(t);

	Cone c(1, 3, 16, Color::ORANGE);
	std::shared_ptr<Cone> cone = std::make_shared<Cone>(c);

	std::vector<std::shared_ptr<Mesh>> meshes;
	//meshes.push_back(triangle);
	meshes.push_back(cone);

	rtx::Matrix4 model;
	model.LoadIdentity();
	model = model * VertexProcessor::Scale(rtx::Vector3(0.5f, 0.5f, 0.5f));
	model = model * VertexProcessor::Rotate(30.f, rtx::Vector3::Right());
	model = model * VertexProcessor::Rotate(30.f, rtx::Vector3::Forward());
	//model = model * VertexProcessor::Translate(rtx::Vector3(1.f, -0.5f, 0.f));

	rasterizer.Render(meshes, model, Color(Color::GRAY));
	rasterizer.Save("image.tga");

	return 0;
}
