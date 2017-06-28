#pragma once

#include "Log.h"

namespace ShuangLong
{
	class DirectoryUtilTest sealed
	{
	private:
		DirectoryUtilTest();
		Log* mpLog = nullptr;

	public:
		~DirectoryUtilTest();

		static DirectoryUtilTest *mpInstance;
		static void Entry();

		void DirectoryUtilTest_Try();
	};
}
