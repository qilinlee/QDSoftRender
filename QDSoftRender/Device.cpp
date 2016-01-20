#include "Device.h"
#include "Utility.h"

namespace QDSoftRender
{
	DeviceSP Device::_Instance = nullptr;
	Device::Device(int iWidth, int iHeight, ColorDataType color, unsigned long dwBackColor)
		: m_iWidth(iWidth)
		, m_iHeight(iHeight)
		, m_iPitch(m_iWidth * Color::GetColorDataLength(color))
		, m_eColorType(color)
		, m_pFrameBuffer(nullptr)
		, m_pZBuffer(nullptr)
		, m_BackColor(dwBackColor)
	{
		m_pFrameBuffer = new unsigned int[m_iWidth * m_iHeight];
		m_pZBuffer = new float[m_iWidth * m_iHeight];
	}

	Device::~Device()
	{
		SafeDelete(m_pFrameBuffer);
		SafeDelete(m_pZBuffer);
	}

	QDSoftRender::DeviceSP Device::CreateDevice(int iWidth, int iHeight, ColorDataType color,unsigned long dwBackColor)
	{
		if (nullptr == _Instance)
		{
			_Instance = DeviceSP(new Device(iWidth, iHeight, color, dwBackColor));
		}

		return _Instance;
	}

	void Device::DestroyDevice(DeviceSP device)
	{
		if (nullptr != _Instance)
		{
			_Instance.reset();
			_Instance = nullptr;
		}
	}

	void Device::Clear(DeviceClearFlag flag)
	{
		if ((flag & CLEAR_COLOR) == CLEAR_COLOR)
		{
			for (int i = 0; i < m_iHeight * m_iWidth; ++i)
				m_pFrameBuffer[i] = m_BackColor.Hex();
		}

		if ((flag & CLEAR_ZBUFFER) == CLEAR_ZBUFFER)
		{
			for (int i = 0; i < m_iWidth * m_iHeight; ++i)
				m_pZBuffer[i] = 0.0f;
		}
	}

	void Device::Present(unsigned char *pCanvas)
	{
		memcpy( pCanvas, m_pFrameBuffer, m_iWidth * m_iHeight * Color::GetColorDataLength(m_eColorType));
	}

	void Device::Draw()
	{

	}

}