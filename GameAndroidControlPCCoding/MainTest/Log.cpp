#include "Log.h"

namespace ShuangLong
{
	void Log::Console(const char* msg)
	{
		std::cout << msg << std::endl;
	}

	void Log::WriteFile(const char* msg)
	{
		std::cout << msg << std::endl;
	}
}