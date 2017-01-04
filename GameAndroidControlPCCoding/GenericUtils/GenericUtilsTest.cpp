#include "stdafx.h"
#include "GenericUtilsTest.h"
#include "TimeUtil.h"
#include "CodeLocation.h"

#include <iostream>
#include <iomanip>

ShuangLong::ILog *g_pLog = nullptr;
void GenericUtilsTestEntry(ShuangLong::ILog *pLog)
{
	g_pLog = pLog;
	std::cout << "-------------------------------- Generic Utils Testing --------------------------------" << std::endl;

	g_pLog->Console("Log Testing");
	g_pLog->Console(SL_CODELOCATION, "%d --> %s", 110, "Location Testing");

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

	//GetFileSize()
}