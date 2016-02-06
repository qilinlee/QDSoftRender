#include "Error.h"

namespace QDSoftRender
{
	void Error::ThrowError(unsigned long dwErrorCode, const std::string &strError)
	{
		m_dwErrorCode = dwErrorCode;
		m_strError = strError;
	}
}

