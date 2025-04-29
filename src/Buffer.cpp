#include "../include/Buffer.h"

Buffer::Buffer(const int x, const int y) : _sizeX(x), _sizeY(y)
{
	_colorBuffer.resize(this->_sizeX * this->_sizeY);
	_depthBuffer.resize(this->_sizeX * this->_sizeY);
}

bool Buffer::OpenImage(const char* filename, const unsigned int width, const unsigned int height)
{
	unsigned short header[9] = 
	{
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		width, height,
		0x0820 
	};

	FILE* f = nullptr;
	int err = fopen_s(&f, filename, "rb");
	if (err != 0 || f == nullptr)
		return false;

	fread(header, 2, 9, f);

	_colorBuffer.resize(width * height);
	fread(_colorBuffer.data(), 4, width * height, f);

	fclose(f);

	return true;
}

void Buffer::FillColor(const unsigned int color)
{
	for (int pixel = 0; pixel < _sizeX * _sizeY; ++pixel)
	{
		_colorBuffer[pixel] = color;
	}
}

void Buffer::SetPixel(const int x, const int y, const unsigned int color)
{
	int pixel = x + _sizeX * y;
	_colorBuffer[pixel] = color;
}

void Buffer::FillDepth(const float d) 
{
	for (int i = 0; i < _sizeX * _sizeY; ++i) 
	{
		_depthBuffer[i] = d;
	}
}
