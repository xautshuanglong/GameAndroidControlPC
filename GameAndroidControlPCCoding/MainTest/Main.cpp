#include "Log.h"
#include "StringUtilTest.h"
#include "TimeUtilTest.h"
//#include "GenericUtilsTest.h"

#include <iostream>

class CodeLocationTest
{
public:
	static void Test()
	{
		ShuangLong::CodeLocation testCodeLocation(__FILE__, __FUNCTION__, __LINE__);
		std::cout << "TestClass::  " << testCodeLocation.GetShortClassName() << std::endl;
		std::cout << "TestFunc::  " << testCodeLocation.GetFuncName() << std::endl;
	}
};

int main(int argc, char** argv)
{
	std::cout << "====================================== Main Testing ======================================" << std::endl;
	ShuangLong::Log *pLog = ShuangLong::Log::GetInstance();

	//GenericUtilsTestEntry(pLog);
	//ShuangLong::StringUtilTest::Entry();
	ShuangLong::TimeUtilTest::Entry();

	ShuangLong::CodeLocation testCodeLocation(__FILE__, __FUNCTION__, __LINE__);
	std::cout << "GetShortClassName:" << testCodeLocation.GetShortClassName() << std::endl;
	std::cout << "GetFuncName:" << testCodeLocation.GetFuncName() << std::endl;

	CodeLocationTest::Test();

	return 0;
}