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
}