#pragma once

#ifndef __DRAWHELPER_H__
#define __DRAWHELPER_H__

#include "Device.h"
#include "Math/Math.h"
namespace QDSoftRender
{
	void DrawPixel(DeviceSP spDevice, int iX, int iY, Color color);
	void DrawLine(DeviceSP spDevice, int iOrigX, int iOrigY, int iDstX, int iDstY, Color color);
}
#endif