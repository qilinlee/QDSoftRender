#include "DrawHelper.h"

namespace QDSoftRender
{
	void DrawPixel(DeviceSP spDevice, int iX, int iY, Color color)
	{
		if (nullptr != spDevice)
			spDevice->m_pFrameBuffer[iX + iY * spDevice->m_iWidth] = color.Hex();
	}

	void DrawLine(DeviceSP spDevice, int iOrigX, int iOrigY, int iDstX, int iDstY, Color color)
	{
		if (iOrigX == iDstX && iOrigY == iDstY)
		{
			DrawPixel(spDevice, iOrigX, iOrigY, color);
			return;
		}

		int iDeltaX = iDstX - iOrigX;
		int iXStep = 0;
		if (iDeltaX >= 0)
			iXStep = 1;
		else
		{
			iDeltaX = -iDeltaX;
			iXStep = -1;
		}

		int iDeltaY = iDstY - iOrigX;
		int iYStep = 0;
		if (iDeltaY >= 0.0f)
			iYStep = 1;
		else
		{
			iYStep = -iYStep;
			iDeltaY = -iDeltaY;
		}

		int i2DeltaX = iDeltaX << 1;
		int i2DeltaY = iDeltaY << 1;

		int X = iOrigX;
		int Y = iOrigY;
		if (iDeltaX > iDeltaY)//近X轴直线
		{
			int iError = -iDeltaX;
			for (int i = 0; i <= iDeltaX; ++i)
			{
				DrawPixel(spDevice, X, Y, color);
				X += iXStep;
				iError += i2DeltaY;
				if (iError >= 0)
				{
					Y += iYStep;
					iError -= i2DeltaX;
				}
			}
		}
		else//近Y轴直线
		{
			int iError = -iDeltaY;
			for (int i = 0; i <= iDeltaY; ++i)
			{
				DrawPixel(spDevice, X, Y, color);
				Y += iYStep;
				iError += i2DeltaX;
				if (iError >= 0)
				{
					X += iXStep;
					iError -= i2DeltaY;
				}
			}

		}
	}

}