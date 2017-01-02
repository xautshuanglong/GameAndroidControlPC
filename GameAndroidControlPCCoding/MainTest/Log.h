#pragma once
#include "CommonDefines.h"

#include <CodeLocation.h>
#include <StringUtil.h>

#include <iostream>
#include <fstream>
#include <mutex>

#define SL_DEBUG_ENABLE true
#define SL_DEFAULT_LOGFILE "E:\\TempLog.txt"

namespace ShuangLong
{
	class Log sealed
	{
	private:
		Log();
		static Log* m_pInstance;
		static std::mutex m_mutex;

		std::ofstream m_osFile;

	public:
		~Log();

		static Log* GetInstance();

		void Console(const char* msgFormat, ...);
		void Console(Utils::CodeLocation location, char* msgFormat, ...);
		void WriteFile(const char* msgFormat, ...);
		void WriteFile(Utils::CodeLocation location, char* msgFormat, ...);

	private:
		class Helpper
		{
		public:
			Helpper() {}
			~Helpper()
			{
				if (m_pInstance != nullptr)
				{
					delete m_pInstance;
				}
			}
		};
		static Helpper helpper;
	};
}
