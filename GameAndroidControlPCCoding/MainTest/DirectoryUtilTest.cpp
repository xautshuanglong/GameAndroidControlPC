#include "stdafx.h"
#include "DirectoryUtilTest.h"

namespace ShuangLong
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
	}

	void DirectoryUtilTest::DirectoryUtilTest_Try()
	{
		char curDirBuffer[512];
		GetCurrentDirectoryA(512, curDirBuffer);
		mpLog->Console("Current Directory: %s", curDirBuffer);

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
	}
}
