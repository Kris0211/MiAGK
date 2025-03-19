#include "../include/Buffer.h"

Buffer::Buffer(const int x, const int y) : _sizeX(x), _sizeY(y)
{
	_colorBuffer.resize(this->_sizeX * this->_sizeY);
}

void Buffer::FillColor(const int color)
{
	for (int pixel = 0; pixel < _sizeX * _sizeY; ++pixel)
	{
		_colorBuffer[pixel] = color;
	}
}
