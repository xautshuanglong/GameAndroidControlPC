#pragma once

#include "Log.h"

namespace ShuangLong
{
	class DirectoryUtilTest sealed
	{
	private:
		Log* mpLog = nullptr;

	public:
		DirectoryUtilTest();
		~DirectoryUtilTest();

		static DirectoryUtilTest *mpInstance;
		static void Entry();

		void DirectoryUtilTest_Try();
	};
}
