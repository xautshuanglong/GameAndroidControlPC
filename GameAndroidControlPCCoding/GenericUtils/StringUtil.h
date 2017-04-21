#pragma once
#include "CommonDefines.h"

#include <iostream>
#include <string>
#include <iterator>
#include <vector>

#define SL_STRINGUTIL_BUFFERLEN 1024

namespace ShuangLong
{
	namespace Utils
	{
		/************************************************************************\
			Author     : JiangChuanbiao
			Date       : 2017-4-21
			Description: 字符串操作工具
						（字符格式化, 剔除空字符" \t\r\n", 字符串分割,
						  款字节与多字节互转）
		\************************************************************************/
		class EXPORT_API StringUtil
		{
		public:
			StringUtil() = delete;
			StringUtil(const StringUtil& originalObj) = delete;
			StringUtil(StringUtil&& originalObj) = delete;

		public:
			std::string static FormatString(const char* format, ...);
			std::wstring static FormatWString(const wchar_t* wFormat, ...);

			std::string static FormatArguments(const char* format, va_list argList);
			std::wstring static FormatArgumentsW(const wchar_t* wFormat, va_list argList);

			std::string static Trim(const std::string& original);
			std::wstring static TrimW(const std::wstring& original);

			unsigned int static Split(std::vector<std::string>& v, std::string s, char delimiter, unsigned int maxSegments = INT_MAX);
			unsigned int static SplitW(std::vector<std::wstring>& v, std::wstring s, wchar_t delimiter, unsigned int maxSegments = INT_MAX);

			std::wstring static StringToWStringAPI(const std::string& originalStr);
			std::string static WStringToStringAPI(const std::wstring& originalStr);

			std::string static WStringToString(const std::wstring& originalStr);
			std::wstring static StringToWString(const std::string& originalStr);
		};
	}
}
