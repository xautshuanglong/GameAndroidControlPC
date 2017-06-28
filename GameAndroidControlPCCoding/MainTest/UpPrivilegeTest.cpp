#include "stdafx.h"
#include "UpPrivilegeTest.h"

//#include <shellapi.h>
//#include <tchar.h>

namespace ShuangLong::Test
{
	UpPrivilegeTest::UpPrivilegeTest()
	{
	}

	UpPrivilegeTest::~UpPrivilegeTest()
	{
	}

	bool UpPrivilegeTest::IsOsVersionVistaOrGreater()
	{
		return IsWindowsVersionOrGreater(5, 0, 1);
	}
	//检查并根据系统版本选择打开程序方式  
	void UpPrivilegeTest::ShellExecuteExOpen(LPWSTR appName, LPWSTR appPath)
	{
		if (IsOsVersionVistaOrGreater())
		{
			SHELLEXECUTEINFO sei = {sizeof(SHELLEXECUTEINFO)};
			sei.fMask = SEE_MASK_NOCLOSEPROCESS;
			sei.lpVerb = TEXT("runas");
			sei.lpFile = appName;
			sei.lpDirectory = appPath;
			sei.nShow = SW_SHOWNORMAL;
			if (!ShellExecuteEx(&sei))
			{
				DWORD dwStatus = GetLastError();
				if (dwStatus==ERROR_CANCELLED)
				{
					printf("提升权限被用户拒绝\n");
				}
				else if (dwStatus==ERROR_FILE_NOT_FOUND)
				{
					printf("所要执行的文件没有找到\n");
				}
			}
		}
		else
		{
			ShellExecute(NULL, TEXT("open"), appName, NULL, appPath, SW_SHOWNORMAL);
		}
	}
}

