#include "Util.h"

namespace QDSoftRender
{
	namespace Util
	{
		bool CompareFloat(float f1, float f2, float delta /*= 1e-6f*/)
		{
			float f = f1 - f2;
			return (-delta < f && f < delta);
		}
	}
}