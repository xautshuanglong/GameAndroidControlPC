#pragma once
#include "Log.h"

namespace ShuangLong
{
	class StringUtilTest sealed
	{
	private:
		Log* mpLog = nullptr;

	public:
		StringUtilTest();
		~StringUtilTest();

		static StringUtilTest *mpInstance;
		static void Entry();

		void StringUtilTest_FormateString();
		void StringUtilTest_FormateWString();
		void StringUtilTest_FormatArguments(char *format, ...);
		void StringUtilTest_FormatArgumentsW(wchar_t *format, ...);
		void StringUtilTest_Trim();
		void StringUtilTest_TrimW();
		void StringUtilTest_Split();
		void StringUtilTest_SplitW();
		void StringUtilTest_StringToWStringAPI();
		void StringUtilTest_WStringToStringAPI();
		void StringUtilTest_WStringToString();
		void StringUtilTest_StringToWString();
	};
}

