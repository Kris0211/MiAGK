#pragma once
#include <vector>

class Buffer
{
public:
	Buffer(const int x, const int y);

	void FillColor(const unsigned int color);
	void SetPixel(const int x, const int y, const unsigned int color);

	std::vector<int>& GetColorData() { return _colorBuffer; }

	int GetSizeX() const { return _sizeX; }
	int GetSizeY() const { return _sizeY; }

private:
	std::vector<int> _colorBuffer;

	int _sizeX;
	int _sizeY;
};
