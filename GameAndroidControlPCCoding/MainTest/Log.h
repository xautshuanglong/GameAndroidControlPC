#pragma once

#include <iostream>

#define DEBUG_ENABLE true

namespace ShuangLong
{
	class Log
	{
	public:
		Log() = delete;
		Log(const Log& log) = delete;
		Log(const Log&& log) = delete;

		void static Console(const char* msg);
		void static WriteFile(const char* msg);
	};
}
