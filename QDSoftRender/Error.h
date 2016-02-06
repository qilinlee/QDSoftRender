#pragma once

#ifndef __ERROR_H__
#define __ERROR_H__
#include <string>

namespace QDSoftRender
{
	class Error
	{
	public:
		Error() : m_dwErrorCode(-1), m_strError(""){}
		void ThrowError(unsigned long dwErrorCode, const std::string &strError);
		unsigned long ErrorCode(){ return m_dwErrorCode; }
		const std::string& ErrorString(){ return m_strError; }
	private:
		unsigned long m_dwErrorCode;
		std::string m_strError;
		bool m_bForceExist;
	};
}
#endif
