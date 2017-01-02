#pragma once
#include "CommonDefines.h"

#include <iostream>
#include <string>

#define SL_STRINGUTIL_BUFFERLEN 1024

namespace ShuangLong
{
	namespace Utils
	{
		class EXPORT_API StringUtil
		{
		public:
			StringUtil() = delete;
			StringUtil(const StringUtil& originalObj) = delete;
			StringUtil(const StringUtil&& originalObj) = delete;

		public:
			std::string static FormatString(const char* format, ...);
			std::wstring static FormatWString(const wchar_t* wFormat, ...);

			std::string static FormatArguments(const char* format, va_list argList);
			std::wstring static FormatArgumentsW(const wchar_t* wFormat, va_list argList);
		};
	}
}
