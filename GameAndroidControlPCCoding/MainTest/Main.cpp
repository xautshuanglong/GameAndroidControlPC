#include "Log.h"

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "====================================== Main Testing ======================================" << std::endl;
	ShuangLong::Log::GetInstance()->Console("Log Testing");
	ShuangLong::Log::GetInstance()->Console(SL_CODELOCATION, "%d --> %s", 110, "Location Testing");

	ShuangLong::Log *pLog = ShuangLong::Log::GetInstance();
	pLog->WriteFile("Write File Testing");
	pLog->WriteFile("%d, %s", 234, "Write File Testing");

	return 0;
}