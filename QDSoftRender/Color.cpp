#include "Color.h"
namespace QDSoftRender
{
	const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);
	const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
	const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);

	Color::Color(float fR, float fG, float fB, float fAlpha /*= 1.0f*/)
		: r(fR), g(fG), b(fB), alpha(fAlpha)
	{
		r = Util::Clamp(r, 0.0f, 1.0f);
		g = Util::Clamp(g, 0.0f, 1.0f);
		b = Util::Clamp(b, 0.0f, 1.0f);
		alpha = Util::Clamp(alpha, 0.0f, 1.0f);
		m_dwHex = ToHex();
	}

	Color::Color(unsigned int dwHexColor)
		: m_dwHex(dwHexColor)
	{
		b = (dwHexColor & 0xFF) / 255.0f;
		g = ((dwHexColor & 0xFF00) >> 8) / 255.0f;
		r = ((dwHexColor & 0xFF0000) >> 16) / 255.0f;
		alpha = ((dwHexColor & 0xFF000000) >> 24) / 255.0f;
	}

	unsigned int Color::ToHex()
	{
			unsigned long dwR = static_cast<unsigned long>(round(255.0f * r));
			unsigned long dwG = static_cast<unsigned long>(round(255.0f * g));
			unsigned long dwB = static_cast<unsigned long>(round(255.0f * b));
			unsigned long dwA = static_cast<unsigned long>(round(255.0f * alpha));
			return ((dwA << 24) | (dwR << 16) | (dwG << 8) | dwB);
		}

}