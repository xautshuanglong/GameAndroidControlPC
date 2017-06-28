#pragma once

#include "Log.h"

namespace ShuangLong
{
	namespace Test
	{
		class UpPrivilegeTest sealed
		{
		private:
			UpPrivilegeTest();
			Log* mpLog;

		public:
			~UpPrivilegeTest();

			static UpPrivilegeTest *mpInstance;
			static void Entry();

			bool IsOsVersionVistaOrGreater();
			void ShellExecuteExOpen(LPWSTR appName, LPWSTR appPath);
		};
	}
}

