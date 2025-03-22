#include "include/Buffer.h"
#include "include/FileSaver.h"
#include "include/Rasterizer.h"

constexpr int imgWidth = 512;
constexpr int imgHeight = 512;

constexpr unsigned int A = 0xff;
constexpr unsigned int R_BG = 0x80;
constexpr unsigned int G_BG = 0x00;
constexpr unsigned int B_BG = 0xff;
constexpr unsigned int BG_COLOR = A << 24 | R_BG << 16 | G_BG << 8 | B_BG;

constexpr unsigned int R_FG = 0x00;
constexpr unsigned int G_FG = 0xff;
constexpr unsigned int B_FG = 0x7f;
constexpr unsigned int TRIANGLE_COLOR = A << 24 | R_FG << 16 | G_FG << 8 | B_FG;

int main(int argc, char* argv[])
{
	Buffer buf(imgWidth, imgHeight);
	Rasterizer rasterizer(imgWidth, imgHeight);

	rtx::Triangle tr(
		rtx::Vector3(0.f, -0.5f, 0.f),
		rtx::Vector3(-0.6f, 0.5f, 0.f),
		rtx::Vector3(0.6f, 0.5f, 0.f)
	);

	rasterizer.Render(tr, BG_COLOR, TRIANGLE_COLOR);
	return 0;
}
