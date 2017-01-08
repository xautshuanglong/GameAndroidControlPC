#include "stdafx.h"
#include "GenericUtilsTest.h"
#include "TimeUtil.h"
#include "CodeLocation.h"

#include <iostream>
#include <iomanip>
#include <windows.h>

ShuangLong::ILog *g_pLog = nullptr;
void GenericUtilsTestEntry(ShuangLong::ILog *pLog)
{
	g_pLog = pLog;
	std::cout << "-------------------------------- Generic Utils Testing --------------------------------" << std::endl;

	g_pLog->Console(SL_CODELOCATION, "%d --> %s", 110, "Location Testing");

	std::cout << std::endl << "---------------------------------- Time Utils Testing ----------------------------------" << std::endl;
	long long frequency = ShuangLong::Utils::TimeUtil::QueryPerformanceFrequency();
	std::cout << "frequency: " << frequency << std::endl;
	long long curWinTime = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
	std::cout << "curWinTime: " << curWinTime << std::endl;
	g_pLog->Console(SL_CODELOCATION, "PerformanceCounter: %llu", curWinTime);
	g_pLog->Console(SL_CODELOCATION, "%x", '\t');

	std::cout << std::endl << "---------------------------------- Directory Testing ----------------------------------" << std::endl;
	char curDirBuffer[512];
	GetCurrentDirectoryA(512, curDirBuffer);
	g_pLog->Console("Current Directory: %s", curDirBuffer);

	char fullPathBuffer[512];
	char *pFilePart = nullptr;
	GetFullPathNameA("Log.h", 512, fullPathBuffer, &pFilePart);
	g_pLog->Console("Full Path: %s", fullPathBuffer);
	g_pLog->Console("File Name : %s", pFilePart);

	DWORD fileAttributes = GetFileAttributesA("Log.h");
	g_pLog->Console("File Attribut : %d", fileAttributes);

	WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
	BOOL success = GetFileAttributesExA("Log.h", GetFileExInfoStandard, &fileAttributeData);
	if (success == 0)
	{
		g_pLog->Console(SL_CODELOCATION, "Get file attributes faild %d", GetLastError());
	}
	else
	{
		g_pLog->Console("FileAttributes=%d      FileSizeHigh=%d      FileSizeLow=%d", 
			fileAttributeData.dwFileAttributes, fileAttributeData.nFileSizeHigh, fileAttributeData.nFileSizeLow);

		unsigned long long ulongTime = fileAttributeData.ftCreationTime.dwHighDateTime;
		ulongTime = ulongTime << 32 | fileAttributeData.ftCreationTime.dwLowDateTime;
		g_pLog->Console("CreationTime: 0x%X  0x%X    ulong: %llu", 
			fileAttributeData.ftCreationTime.dwHighDateTime, fileAttributeData.ftCreationTime.dwLowDateTime, ulongTime);

		SYSTEMTIME sysTime;
		FILETIME localFileTime;
		FileTimeToLocalFileTime(&fileAttributeData.ftCreationTime, &localFileTime);
		FileTimeToSystemTime(&localFileTime, &sysTime);
		g_pLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d", 
			sysTime.wYear, sysTime.wMonth, sysTime.wDay, 
			sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

		FileTimeToLocalFileTime(&fileAttributeData.ftLastWriteTime, &localFileTime);
		FileTimeToSystemTime(&localFileTime, &sysTime);
		g_pLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
			sysTime.wYear, sysTime.wMonth, sysTime.wDay,
			sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

		FileTimeToLocalFileTime(&fileAttributeData.ftLastAccessTime, &localFileTime);
		FileTimeToSystemTime(&localFileTime, &sysTime);
		g_pLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
			sysTime.wYear, sysTime.wMonth, sysTime.wDay,
			sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

		ULARGE_INTEGER largeTime;
		largeTime.HighPart = fileAttributeData.ftCreationTime.dwHighDateTime;
		largeTime.LowPart = fileAttributeData.ftCreationTime.dwLowDateTime;
		g_pLog->Console("LargeTime: %I64u", largeTime.QuadPart);
		g_pLog->Console("LargeTime: %llu", largeTime.QuadPart);
	}

	//GetFileSize()
}