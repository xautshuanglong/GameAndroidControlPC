#pragma once

namespace ShuangLong
{
	namespace Test
	{
		class UpPrivilegeTest
		{
		public:
			UpPrivilegeTest();
			~UpPrivilegeTest();

			bool IsOsVersionVistaOrGreater();
			void ShellExecuteExOpen(LPWSTR appName, LPWSTR appPath);
		};
	}
}

