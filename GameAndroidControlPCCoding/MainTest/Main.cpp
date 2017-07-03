#include "stdafx.h"
#include "Log.h"
#include "StringUtilTest.h"
#include "TimeUtilTest.h"
#include "DirectoryUtilTest.h"
#include "TestClassTest.h"
#include "UpPrivilegeTest.h"
#include "VersionUtilTest.h"

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "====================================== Main Testing ======================================" << std::endl;
	ShuangLong::Log *pLog = ShuangLong::Log::GetInstance();

	//ShuangLong::StringUtilTest::Entry();
	//ShuangLong::TimeUtilTest::Entry();
	//ShuangLong::DirectoryUtilTest::Entry();
	//ShuangLong::TestClassTest::Entry();
	//ShuangLong::Test::UpPrivilegeTest::Entry();
	ShuangLong::Test::VersionUtilTest::Entry();

	return 0;
}