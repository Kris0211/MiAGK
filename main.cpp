#include "include/Buffer.h"
#include "include/FileSaver.h"

constexpr int imgWidth = 512;
constexpr int imgHeight = 512;

constexpr int A = 0xff;
constexpr int R = 0x80;
constexpr int G = 0x00;
constexpr int B = 0xff;

constexpr int COLOR = A << 24 | R << 16 | G << 8 | B;

int main(int argc, char* argv[])
{
	Buffer buf(imgWidth, imgHeight);
	buf.FillColor(COLOR);
	FileSaver::SaveTGA("image.tga", buf.GetColorData(), imgWidth, imgHeight);
	return 0;
}
