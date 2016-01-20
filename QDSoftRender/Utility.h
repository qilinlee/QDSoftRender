#pragma once

#ifndef __UTILITY_H__
#define __UTILITY_H__

namespace QDSoftRender
{
	template<typename T>
	void SafeDelete(T *p)
	{
		if (nullptr != p)
		{
			delete p;
			p = nullptr;
		}
	}

	template<typename T>
	void SafeDeleteArray(T **p)
	{
		if (nullptr != p)
		{
			delete[] p;
			p = nullptr;
		}
	}
}
#endif