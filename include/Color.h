#pragma once
#include "../RasTerX/include/MathUtils.hpp"

struct Color
{
	unsigned char r, g, b, a;

	Color() :r(0), g(0), b(0), a(0xFF) {}
	Color(const int r, const int g, const int b, const int a = 255) :
		r(static_cast<unsigned char>(rtx::MathUtils::Clamp(r, 0, 255))),
		g(static_cast<unsigned char>(rtx::MathUtils::Clamp(g, 0, 255))),
		b(static_cast<unsigned char>(rtx::MathUtils::Clamp(b, 0, 255))),
		a(static_cast<unsigned char>(rtx::MathUtils::Clamp(a, 0, 255)))
	{
	}

	explicit Color(const float r, const float g, const float b, const float a = 1.0f) :
		r(static_cast<unsigned char>(rtx::MathUtils::Clamp(r, 0.0f, 1.0f) * 255)),
		g(static_cast<unsigned char>(rtx::MathUtils::Clamp(g, 0.0f, 1.0f) * 255)),
		b(static_cast<unsigned char>(rtx::MathUtils::Clamp(b, 0.0f, 1.0f) * 255)),
		a(static_cast<unsigned char>(rtx::MathUtils::Clamp(a, 0.0f, 1.0f) * 255))
	{
	}

	Color(unsigned int hex) :
		a((hex >> 24) & 0xFF),
		r((hex >> 16) & 0xFF),
		g((hex >> 8) & 0xFF),
		b(hex & 0xFF)
	{
	}

	Color(rtx::Vector3 v, const float a = 1.0f) :
		r(static_cast<unsigned char>(rtx::MathUtils::Clamp(v.x, 0.0f, 1.0f) * 255)),
		g(static_cast<unsigned char>(rtx::MathUtils::Clamp(v.y, 0.0f, 1.0f) * 255)),
		b(static_cast<unsigned char>(rtx::MathUtils::Clamp(v.z, 0.0f, 1.0f) * 255)),
		a(static_cast<unsigned char>(rtx::MathUtils::Clamp(a, 0.0f, 1.0f) * 255))
	{
	}

	unsigned int ToHex() const
	{
		return a << 24 | r << 16 | g << 8 | b;
	}

	rtx::Vector3 ToVector() const
	{
		return rtx::Vector3(
			static_cast<float>(r) / 255.0f,
			static_cast<float>(g) / 255.0f,
			static_cast<float>(b) / 255.0f
		);
	}

	static const unsigned int RED = 0xFFFF0000;
	static const unsigned int GREEN = 0xFF00FF00;
	static const unsigned int BLUE = 0xFF0000FF;

	static const unsigned int BLACK = 0xFF000000;
	static const unsigned int WHITE = 0xFF000000;
	static const unsigned int GRAY = 0xFF808080;

	static const unsigned int CYAN = 0xFF00FFFF;
	static const unsigned int MAGENTA = 0xFFFF00FF;
	static const unsigned int YELLOW = 0xFFFFFF00;

	static const unsigned int ORANGE = 0xFFFF8000;
	static const unsigned int LIME = 0xFF80FF00;
	static const unsigned int ROSE = 0xFFFF0080;
	static const unsigned int VIOLET = 0xFF8000FF;
	static const unsigned int SPRING_GREEN = 0xFF00FF80;
	static const unsigned int AZURE = 0xFF0080FF;
};
