#include "GenericUtilsTest.h"
#include "Log.h"

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "====================================== Main Testing ======================================" << std::endl;
	ShuangLong::Log *pLog = ShuangLong::Log::GetInstance();

	GenericUtilsTestEntry(pLog);

	return 0;
}