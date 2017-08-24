#include "stdafx.h"
#include "DirectoryUtilTest.h"

#include <StringUtil.h>

namespace Shuanglong::Test
{
	DirectoryUtilTest* DirectoryUtilTest::mpInstance = nullptr;

	DirectoryUtilTest::DirectoryUtilTest()
	{
		;
	}

	DirectoryUtilTest::~DirectoryUtilTest()
	{
		;
	}

	void DirectoryUtilTest::Entry()
	{
		mpInstance = new DirectoryUtilTest();
		mpInstance->mpLog = Log::GetInstance();

		std::cout << std::endl << "----------------------------------- Directory Utils Testing -----------------------------------" << std::endl;
		mpInstance->DirectoryUtilTest_Try();
		mpInstance->DirectoryUtilTest_GetEnv();
	}

	void DirectoryUtilTest::DirectoryUtilTest_Try()
	{
		char curDirBuffer[512];
		GetCurrentDirectoryA(512, curDirBuffer);
		mpLog->Console("Current Directory: %s", curDirBuffer);

		char curModuleFileName[MAX_PATH];
		DWORD res = GetModuleFileNameA(nullptr, curModuleFileName, MAX_PATH);
		mpLog->Console(SL_CODELOCATION, "curModuleFileName=%s", curModuleFileName);

		char *pOutFileName = new char[MAX_PATH];
		_get_pgmptr(&pOutFileName);
		mpLog->Console(SL_CODELOCATION, "pOutFileName = %s", pOutFileName);

		char fullPathBuffer[512];
		char *pFilePart = nullptr;
		GetFullPathNameA("Log.h", 512, fullPathBuffer, &pFilePart);
		mpLog->Console("Full Path: %s", fullPathBuffer);
		mpLog->Console("File Name : %s", pFilePart);

		DWORD fileAttributes = GetFileAttributesA("Log.h");
		mpLog->Console("File Attribut : %d", fileAttributes);

		WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
		BOOL success = GetFileAttributesExA("Log.h", GetFileExInfoStandard, &fileAttributeData);
		if (success == 0)
		{
			mpLog->Console(SL_CODELOCATION, "Get file attributes faild %d", GetLastError());
		}
		else
		{
			mpLog->Console("FileAttributes=%d      FileSizeHigh=%d      FileSizeLow=%d",
				fileAttributeData.dwFileAttributes, fileAttributeData.nFileSizeHigh, fileAttributeData.nFileSizeLow);

			unsigned long long ulongTime = fileAttributeData.ftCreationTime.dwHighDateTime;
			ulongTime = ulongTime << 32 | fileAttributeData.ftCreationTime.dwLowDateTime;
			mpLog->Console("CreationTime: 0x%X  0x%X    ulong: %llu",
				fileAttributeData.ftCreationTime.dwHighDateTime, fileAttributeData.ftCreationTime.dwLowDateTime, ulongTime);

			SYSTEMTIME sysTime;
			FILETIME localFileTime;
			FileTimeToLocalFileTime(&fileAttributeData.ftCreationTime, &localFileTime);
			FileTimeToSystemTime(&localFileTime, &sysTime);
			mpLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
				sysTime.wYear, sysTime.wMonth, sysTime.wDay,
				sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

			FileTimeToLocalFileTime(&fileAttributeData.ftLastWriteTime, &localFileTime);
			FileTimeToSystemTime(&localFileTime, &sysTime);
			mpLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
				sysTime.wYear, sysTime.wMonth, sysTime.wDay,
				sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

			FileTimeToLocalFileTime(&fileAttributeData.ftLastAccessTime, &localFileTime);
			FileTimeToSystemTime(&localFileTime, &sysTime);
			mpLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
				sysTime.wYear, sysTime.wMonth, sysTime.wDay,
				sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

			ULARGE_INTEGER largeTime;
			largeTime.HighPart = fileAttributeData.ftCreationTime.dwHighDateTime;
			largeTime.LowPart = fileAttributeData.ftCreationTime.dwLowDateTime;
			mpLog->Console("LargeTime: %I64u", largeTime.QuadPart);
			mpLog->Console("LargeTime: %llu", largeTime.QuadPart);
		}

		BOOL existFlag = PathFileExists(L"E:\\TempLog.txt");// Shlwapi.h Shlwapi.lib
		mpLog->Console(SL_CODELOCATION, "existFlag=%s", existFlag ? "true" : "false");
	}

	void DirectoryUtilTest::DirectoryUtilTest_GetEnv()
	{
		size_t     returnValue       = 0;
		errno_t    errorCode         = 0;
		BOOL       retBool           = FALSE;
		char       buffer[MAX_PATH];

		errorCode = getenv_s(&returnValue, buffer, MAX_PATH, "HomePath");
		mpLog->Console(SL_CODELOCATION, "HomePath=%s ErrorCode=%d", buffer, errorCode);

		errorCode = getenv_s(&returnValue, buffer, MAX_PATH, "UserProfile");
		mpLog->Console(SL_CODELOCATION, "UserProfile=%s ErrorCode=%d", buffer, errorCode);

		errorCode = _putenv_s("PUTENV_TEST", "PUTENV_TEST FROM GameAndroidControlPC");
		mpLog->Console(SL_CODELOCATION, "After _putenv_s PUTENV_TEST ErrorCode=%d", errorCode);

		errorCode = getenv_s(&returnValue, buffer, MAX_PATH, "PUTENV_TEST");
		mpLog->Console(SL_CODELOCATION, "PUTENV_TEST=%s  ErrorCode=%d", buffer, errorCode);

		LPITEMIDLIST pidl;
		SHGetSpecialFolderLocation(NULL, CSIDL_LOCAL_APPDATA, &pidl);

		retBool = SHGetSpecialFolderPathA(nullptr, buffer, CSIDL_LOCAL_APPDATA, false);
		mpLog->Console(SL_CODELOCATION, "CSIDL_LOCAL_APPDATA=%s  ReturnBool=%s", buffer, retBool?"true":"false");

		retBool = SHGetSpecialFolderPathA(nullptr, buffer, CSIDL_PROFILE, false);
		mpLog->Console(SL_CODELOCATION, "CSIDL_PROFILE=%s  ReturnBool=%s", buffer, retBool ? "true" : "false");

		WCHAR *wpBuffer = new WCHAR[MAX_PATH];
		SHGetKnownFolderPath(FOLDERID_Downloads, 0, nullptr, &wpBuffer);
		mpLog->Console(SL_CODELOCATION, "FOLDERID_Downloads=%s", Utils::StringUtil::WStringToString(wpBuffer).c_str());

		CoTaskMemFree(wpBuffer);
	}
}
