#include "Log.h"

#include <CodeLocation.h>

#include <iostream>


int main(int argc, char** argv)
{
	std::cout << "====================================== Main Testing ======================================" << std::endl;
	SL_CODELOCATION;

	ShuangLong::Log::Console("test");

	return 0;
}