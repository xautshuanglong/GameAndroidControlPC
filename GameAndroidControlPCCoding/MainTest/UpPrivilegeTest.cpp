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
	//��鲢����ϵͳ�汾ѡ��򿪳���ʽ  
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
					printf("����Ȩ�ޱ��û��ܾ�\n");
				}
				else if (dwStatus==ERROR_FILE_NOT_FOUND)
				{
					printf("��Ҫִ�е��ļ�û���ҵ�\n");
				}
			}
		}
		else
		{
			ShellExecute(NULL, TEXT("open"), appName, NULL, appPath, SW_SHOWNORMAL);
		}
	}
}

