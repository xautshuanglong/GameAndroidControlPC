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

		std::string StringUtil::Trim(const std::string& original)
		{
			static const char* whiteSpace = " \t\r\n";
			if (original.empty() || original.length()==0)
			{
				return original;
			}
			std::string::size_type begin = original.find_first_not_of(whiteSpace);
			if (begin == std::string::npos)
			{
				return "";
			}
			std::string::size_type end = original.find_last_not_of(whiteSpace);
			return std::string(original, begin, end - begin + 1);
		}

		std::wstring StringUtil::WTrim(const std::wstring& original)
		{
			static const wchar_t* whiteSpace = L" \t\r\n";
			if (original.empty() || original.length() == 0)
			{
				return original;
			}
			std::string::size_type begin = original.find_first_not_of(whiteSpace);
			if (begin == std::string::npos)
			{
				return L"";
			}
			std::wstring::size_type end = original.find_last_not_of(whiteSpace);
			return std::wstring(original, begin, end - begin + 1);
		}
	}
}
