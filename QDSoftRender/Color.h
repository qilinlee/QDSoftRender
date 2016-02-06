#pragma once

#ifndef __COLOR_H__
#define __COLOR_H__
#include "math/Math.h"
#include <cmath>
namespace QDSoftRender
{
	enum ColorDataType
	{
		COLOR_DEFAULT = 0,
		COLOR_R8G8B8A8 = 0,
		COLOR_R8G8B8,
	};

	class Color
	{
	public:
		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;

		static int GetColorDataLength(ColorDataType type)
		{
			switch (type)
			{
			case QDSoftRender::COLOR_R8G8B8A8:
				return 4;
			case QDSoftRender::COLOR_R8G8B8:
				return 3;
			default:
				return 4;
			}
		}
	public:
		Color(float fR, float fG, float fB, float fAlpha = 1.0f);
		Color(unsigned int dwHexColor);

		unsigned int Hex(){ return m_dwHex; }

	private:
		unsigned int ToHex();

	public:
		float r;
		float g;
		float b;
		float alpha;
	private:
		unsigned int m_dwHex;
	};
}
#endif