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

	rtx::Triangle tr1(
		rtx::Vector3(-0.3f, 1.2f, 0.f),
		rtx::Vector3(0.2f, 0.4f, 0.f),
		rtx::Vector3(-0.8f, 0.4f, 0.f)
	);

	rtx::Triangle tr2(
		rtx::Vector3(-0.8f, 0.4f, 0.f),
		rtx::Vector3(0.2f, 0.4f, 0.f),
		rtx::Vector3(-0.3f, -0.4f, 0.f)
	);

	rtx::Triangle tr3(
		rtx::Vector3(-0.3f, 0.0f, -0.5f),
		rtx::Vector3(-0.05f, -0.5f, 0.5f),
		rtx::Vector3(-0.55f, -0.5f, 0.5f)
	);

	std::vector<rtx::Triangle> tris = { tr1, tr2, tr3 };

	rtx::Matrix4 model1;
	model1.LoadIdentity();
	model1 = model1 * VertexProcessor::Scale(rtx::Vector3(2.f, 1.f, 0.5f));
	model1 = model1 * VertexProcessor::Rotate(45.f, rtx::Vector3(0.f, 0.f, 1.f));

	rtx::Matrix4 model2;
	model2.LoadIdentity();
	model2 = model2 * VertexProcessor::Rotate(-45.f, rtx::Vector3(0.f, 0.f, 1.f));

	rtx::Matrix4 model3;
	model3.LoadIdentity();
	model3 = model3 * VertexProcessor::Rotate(30.f, rtx::Vector3(0.f, 0.f, 1.f));
	model3 = model3 * VertexProcessor::Translate(rtx::Vector3(0.f, -2.f, 0.f));

	std::vector<rtx::Matrix4> models = { model1, model2, model3 };

	rasterizer.Render(tris, models, Color(Color::GRAY));
	rasterizer.Save("image.tga");

	return 0;
}
