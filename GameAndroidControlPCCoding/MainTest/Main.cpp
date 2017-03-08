#include "Log.h"
#include "StringUtilTest.h"
#include "TimeUtilTest.h"
//#include "GenericUtilsTest.h"

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "====================================== Main Testing ======================================" << std::endl;
	ShuangLong::Log *pLog = ShuangLong::Log::GetInstance();

	//GenericUtilsTestEntry(pLog);
	ShuangLong::StringUtilTest::Entry();
	ShuangLong::TimeUtilTest::Entry();

	return 0;
}