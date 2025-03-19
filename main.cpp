#include "include/Buffer.h"
#include "include/FileSaver.h"

constexpr int imgWidth = 512;
constexpr int imgHeight = 512;

int main(int argc, char* argv[])
{
	Buffer buf(imgWidth, imgHeight);
	buf.FillColor(0xff8000ff);
	FileSaver::SaveTGA("image.tga", buf.GetColorData(), imgWidth, imgHeight);
	return 0;
}
