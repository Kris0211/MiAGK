#include "include/Buffer.h"
#include "include/FileSaver.h"
#include "include/Rasterizer.h"
#include "include/Color.h"

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
		rtx::Vector3(0.2f, 0.4f, 0.f),
		rtx::Vector3(1.2f, 0.4f, 0.f),
		rtx::Vector3(0.7f, -0.4f, 0.f)
	);

	rtx::Triangle tr3(
		rtx::Vector3(-0.25f, 0.0f, 0.f),
		rtx::Vector3(0.0f, -0.5f, 0.f),
		rtx::Vector3(-0.5f, -0.5f, 0.f)
	);

	std::vector<rtx::Triangle> tris = { tr1, tr2, tr3 };

	rasterizer.Render(tris, Color(Color::GRAY));
	rasterizer.Save("image.tga");

	return 0;
}
