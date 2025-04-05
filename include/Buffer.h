#pragma once
#include <vector>

class Buffer
{
public:
	Buffer(const int x, const int y);

	void FillColor(const unsigned int color);
	void SetPixel(const int x, const int y, const unsigned int color);

	void FillDepth(const float d);
	void SetDepthAt(int x, int y, float value) { _depthBuffer[x + _sizeX * y] = value; }

	std::vector<int>& GetColorData() { return _colorBuffer; }
	float GetDepthAt(int x, int y) const { return _depthBuffer[x + _sizeX * y]; }

	int GetSizeX() const { return _sizeX; }
	int GetSizeY() const { return _sizeY; }

private:
	std::vector<int> _colorBuffer;
	std::vector<float> _depthBuffer;

	int _sizeX;
	int _sizeY;
};
