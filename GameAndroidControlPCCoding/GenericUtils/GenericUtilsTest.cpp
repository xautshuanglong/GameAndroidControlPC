#include "stdafx.h"
#include "GenericUtilsTest.h"
#include "TimeUtil.h"
#include "CodeLocation.h"
#include "StringUtil.h"

#include <iostream>
#include <iomanip>
#include <windows.h>

ShuangLong::ILog *g_pLog = nullptr;
void GenericUtilsTestEntry(ShuangLong::ILog *pLog)
{
	g_pLog = pLog;
	std::cout << "-------------------------------- Generic Utils Testing --------------------------------" << std::endl;

	//TimeUtilTest();// 时间相关测试
	//DirectoryUtilTest();// 文件目录相关操作测试
	StringUtilTest();
}

void TimeUtilTest()
{
	std::cout << std::endl << "---------------------------------- Time Utils Testing ----------------------------------" << std::endl;
	long long frequency = ShuangLong::Utils::TimeUtil::QueryPerformanceFrequency();
	std::cout << "frequency: " << frequency << std::endl;
	long long curWinTime = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
	std::cout << "curWinTime: " << curWinTime << std::endl;
	g_pLog->Console(SL_CODELOCATION, "PerformanceCounter: %llu", curWinTime);
	g_pLog->Console(SL_CODELOCATION, "Current Full Time String: %s", ShuangLong::Utils::TimeUtil::GetFullTimeString().c_str());

	time_t timeTest;
	tm tmStruct;
	time(&timeTest);
	timeTest += 28800;
	gmtime_s(&tmStruct, &timeTest);
	g_pLog->Console(SL_CODELOCATION, "gmtimes %04d-%02d-%02d %02d:%02d:%02d", tmStruct.tm_year + 1900, tmStruct.tm_mon + 1, tmStruct.tm_mday, tmStruct.tm_hour, tmStruct.tm_min, tmStruct.tm_sec);

	tm gmTime;
	tm loTime;
	gmtime_s(&gmTime, &timeTest);
	time_t gmt = mktime(&gmTime);
	localtime_s(&loTime, &timeTest);
	time_t lot = mktime(&loTime);
	double diff = difftime(gmt, lot);
	g_pLog->Console(SL_CODELOCATION, "diff = %lf", diff);

	_tzset();

	int dayLight;
	_get_daylight(&dayLight);

	long timeZone;
	int errorCode = _get_timezone(&timeZone);

	char timeZoneName[64];
	size_t t;
	_get_tzname(&t, timeZoneName, sizeof(timeZoneName), 0);

	g_pLog->Console(SL_CODELOCATION, "dayLight=%d timeZone=%ld[%d] zoneName=%s", dayLight, timeZone, errorCode, timeZoneName);

	DWORD tickCount = GetTickCount();
	clock_t clock = ::clock();
	LONGLONG counter = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
	Sleep(1000);
	DWORD tickCount2 = GetTickCount();
	clock_t clock2 = ::clock();
	LONGLONG counter2 = ShuangLong::Utils::TimeUtil::QueryPerformanceCounter();
	g_pLog->Console("tickCount = %lu     clock = %ld     counter = %llu", tickCount2 - tickCount, clock2 - clock, (counter2 - counter)*1000/frequency);
}

/*****************************************************************************\
  Description: some functions to test DirectoryUtil's methods
  Author and Date: JiangShuanglong 2017-2-5 20:35:28
\*****************************************************************************/
void DirectoryUtilTest()
{
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
}

/*****************************************************************************\
  Description: some functions to test StringUtil's methods
  Author and Date: JiangShuanglong 2017-2-5 20:29:35
\*****************************************************************************/
void StringUtilTest()
{
	//StringUtilTest_Trim();
	//StringUtilTest_TrimW();
	//StringUtilTest_Split();
	//StringUtilTest_SplitW();
	StringUtilTest_StringToWStringAPI();
	StringUtilTest_WStringToStringAPI();
	StringUtilTest_WStringToString();
}

void StringUtilTest_Trim()
{
	std::cout << std::endl << "-------------------------------- StringUtilTest_Trim --------------------------------" << std::endl;
	std::string test = "\t sdfsdf  sdfsdf  \t";
	std::cout << "BEGIN" << test << "END" << std::endl;
	std::cout << "BEGIN:" << ShuangLong::Utils::StringUtil::Trim(test) << "END" << std::endl;
}

void StringUtilTest_TrimW()
{
	std::cout << std::endl << "-------------------------------- StringUtilTest_TrimW --------------------------------" << std::endl;
	std::wstring wtest = L"\t sdfsdf  sdfsdf  \t";
	std::wcout << "BEGIN" << wtest << "END" << std::endl;
	std::wcout << "BEGIN:" << ShuangLong::Utils::StringUtil::TrimW(wtest) << "END" << std::endl;
}

void StringUtilTest_Split()
{
	std::cout << std::endl << "-------------------------------- StringUtilTest_Split --------------------------------" << std::endl;
	std::vector<std::string> nameVector;
	std::string nameString = "zhangsan,lisi,wanger,mazi";
	unsigned int count = ShuangLong::Utils::StringUtil::Split(nameVector, nameString, ',');
	
	g_pLog->Console(SL_CODELOCATION, "count=%u  nameString=%s", count, nameString.c_str());
	
	//for (int i = 0; i < count; i++)
	//{
	//	g_pLog->Console("name[%d] = %s", i, nameVector[i].c_str());
	//}

	std::vector<std::string>::iterator it;
	int index = 0;
	for (it = nameVector.begin(); it != nameVector.end(); it++)
	{
		g_pLog->Console("name[%d] = %s", index++, it->c_str());
	}
}

void StringUtilTest_SplitW()
{
	std::cout << std::endl << "-------------------------------- StringUtilTest_SplitW --------------------------------" << std::endl;
	std::vector<std::wstring> nameVector;
	std::wstring nameString = L"zhangsan,lisi,wanger,mazi";
	unsigned int count = ShuangLong::Utils::StringUtil::SplitW(nameVector, nameString, L',');

	//g_pLog->Console(SL_CODELOCATION, "count=%u  nameString=%s", count, std::string(nameString.begin(), nameString.end()).c_str());
	g_pLog->Console(SL_CODELOCATION, "count=%u  nameString=%s", count, ShuangLong::Utils::StringUtil::WStringToStringAPI(nameString).c_str());

	std::vector<std::wstring>::iterator it;
	int index = 0;
	for (it = nameVector.begin(); it != nameVector.end(); it++)
	{
		//g_pLog->Console("name[%d] = %s", index++, std::string(it->begin(), it->end()).c_str());
		g_pLog->Console("name[%d] = %s", index++, ShuangLong::Utils::StringUtil::WStringToStringAPI(it->c_str()).c_str());
	}
}

void StringUtilTest_StringToWStringAPI()
{
	std::cout << std::endl << "-------------------------------- StringUtilTest_StringToWStringAPI --------------------------------" << std::endl;
	std::string testStr = "转换测试：Convert string to wstring";
	std::cout << "String: " << testStr << std::endl;
	std::wstring tempWString = ShuangLong::Utils::StringUtil::StringToWStringAPI(testStr);
	std::wcout << L"WString: " << ShuangLong::Utils::StringUtil::StringToWStringAPI(testStr) << std::endl;
}

void StringUtilTest_WStringToStringAPI()
{
	std::cout << std::endl << "-------------------------------- StringUtilTest_WStringToStringAPI --------------------------------" << std::endl;
	std::wstring testWStr = L"转换测试：Convert wstring to string";
	std::wcout << L"WString: " << testWStr << std::endl;
	std::cout << "String: " << ShuangLong::Utils::StringUtil::WStringToStringAPI(testWStr) << std::endl;
}

void StringUtilTest_WStringToString()
{
	std::cout << std::endl << "-------------------------------- StringUtilTest_WStringToString --------------------------------" << std::endl;
	std::wstring testWStr = L"转换测试：Convert wstring to string";
	std::wcout << L"WString: " << testWStr << std::endl;
	std::cout << "String: " << ShuangLong::Utils::StringUtil::WStringToString(testWStr) << std::endl;
}
