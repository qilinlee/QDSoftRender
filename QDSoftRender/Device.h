#pragma once

#ifndef __DEVICE_H__
#define __DEVICE_H__
#include <memory>
#include "Color.h"

namespace QDSoftRender
{
	enum DeviceClearFlag
	{
		CLEAR_COLOR = 1,
		CLEAR_ZBUFFER = 2,

		CLEAR_ALL = CLEAR_COLOR | CLEAR_ZBUFFER,

	};

	class Device;
	typedef std::shared_ptr<Device> DeviceSP;
	class Device
	{
	public:
		static DeviceSP CreateDevice(int iWidth, int iHeight,ColorDataType color,unsigned long dwBackColor);
		static void DestroyDevice(DeviceSP device);

		~Device();

		void Clear(DeviceClearFlag flag);
		void Draw();
		void Present(unsigned char *pCanvas);
	private:
		Device(int iWidth,int iHeight,ColorDataType color,unsigned long dwBackColor = 0xFFFFFFFF);
		Device(const Device &src);
		Device& operator=(const Device &src);

		
	private:
		static DeviceSP _Instance;

		int m_iWidth;
		int m_iHeight;
		int m_iPitch;
		ColorDataType m_eColorType;
		unsigned int *m_pFrameBuffer;
		float *m_pZBuffer;
		Color m_BackColor;
	};
}
#endif