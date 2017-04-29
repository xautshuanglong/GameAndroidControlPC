#include "Log.h"
#include "StringUtilTest.h"
#include "TimeUtilTest.h"
#include "DirectoryUtilTest.h"

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "====================================== Main Testing ======================================" << std::endl;
	ShuangLong::Log *pLog = ShuangLong::Log::GetInstance();

	//ShuangLong::StringUtilTest::Entry();
	ShuangLong::TimeUtilTest::Entry();
	//ShuangLong::DirectoryUtilTest::Entry();

	return 0;
}