#include "../include/Buffer.h"

Buffer::Buffer(const int x, const int y) : _sizeX(x), _sizeY(y)
{
	_colorBuffer.resize(this->_sizeX * this->_sizeY);
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
