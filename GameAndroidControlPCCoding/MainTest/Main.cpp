#include "Log.h"

#include <TimeUtil.h>

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "====================================== Main Testing ======================================" << std::endl;
	ShuangLong::Log::GetInstance()->Console("Log Testing");
	ShuangLong::Log::GetInstance()->Console(SL_CODELOCATION, "%d --> %s", 110, "Location Testing");

	ShuangLong::Log *pLog = ShuangLong::Log::GetInstance();
	pLog->WriteFile("Write File Testing");
	pLog->WriteFile("%d, %s", 234, "Write File Testing");

	std::cout << ShuangLong::Utils::TimeUtil::GetFullTimeString() << std::endl;
	std::cout << ShuangLong::Utils::TimeUtil::GetSimpleTimeString() << std::endl;
	std::cout << ShuangLong::Utils::TimeUtil::GetFormatTimeString("%D") << std::endl;

	std::cout << ShuangLong::Utils::TimeUtil::GetFullTimestamp() << std::endl;
	std::cout << ShuangLong::Utils::TimeUtil::GetSimpleTimestamp() << std::endl;

	return 0;
}