#include "stdafx.h"
#include "StringUtil.h"


namespace ShuangLong
{
	namespace Utils
	{
		std::string StringUtil::FormatString(const char* format, ...)
		{
			va_list argList;
			va_start(argList, format);
			std::string retString = FormatArguments(format, argList);
			va_end(argList);

			return retString;
		}

		std::string StringUtil::FormatArguments(const char* format, va_list argList)
		{
			std::string retString;
			char buffer[SL_STRINGUTIL_BUFFERLEN];
			_vsnprintf_s(buffer, SL_STRINGUTIL_BUFFERLEN, _TRUNCATE, format, argList);
			retString = buffer;

			return retString;
		}

		std::wstring StringUtil::FormatWString(const wchar_t* wFormat, ...)
		{
			va_list argList;
			va_start(argList, wFormat);
			std::wstring retString = FormatArgumentsW(wFormat, argList);
			va_end(argList);

			return retString;
		}

		std::wstring StringUtil::FormatArgumentsW(const wchar_t* wFormat, va_list argList)
		{
			std::wstring retString;
			wchar_t buffer[SL_STRINGUTIL_BUFFERLEN];
			_vsnwprintf_s(buffer, SL_STRINGUTIL_BUFFERLEN, _TRUNCATE, wFormat, argList);
			retString = buffer;

			return retString;
		}
	}
}
