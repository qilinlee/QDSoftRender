#pragma once

#ifndef __UTIL_H___
#define __UTIL_H___
namespace QDSoftRender
{
	namespace Util
	{
		template<typename T>
		T Clamp(T value, T min, T max)
		{
			return (value < min ? min : (value > max ? max : value));
		}

		template<typename T1, typename T2>
		T1 Lerp(T1 data1, T1 data2, T2 scalar)
		{
			return data1 + (data2 - data1) * scalar;
		}

		bool CompareFloat(float f1, float f2, float delta = 1e-6f);

	}
}

#endif