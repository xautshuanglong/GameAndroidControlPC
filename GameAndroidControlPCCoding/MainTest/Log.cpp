#include "Log.h"

#include <windows.h>

namespace ShuangLong
{
	volatile bool Log::m_bInitFlag = false;
	Log::Helpper Log::helpper;
	Log* Log::m_pInstance = nullptr;
	std::mutex Log::m_mutex;

	Log::Log()
	{
		//std::cout << "Log::Log()" << std::endl;
		m_osFile.open(SL_DEFAULT_LOGFILE, std::ios::out);
	}

	Log::~Log()
	{
		//std::cout << "Log::~Log()" << std::endl;
		if (m_osFile.is_open())
		{
			m_osFile.close();
		}
	}

	Log* Log::GetInstance()
	{
		if (m_bInitFlag==false && m_pInstance==nullptr)
		{
			//std::lock_guard<std::mutex> lock(m_mutex);
			m_mutex.lock();
			if (m_bInitFlag==false && m_pInstance==nullptr)
			{
				m_pInstance = new Log();
				m_bInitFlag = true;
			}
			m_mutex.unlock();
		}

		return m_pInstance;
	}

	void Log::Console(const char* msgFormat, ...)
	{
		if (SL_DEBUG_ENABLE)
		{
			va_list argList;
			va_start(argList, msgFormat);
			std::string msgString = Utils::StringUtil::FormatArguments(msgFormat, argList);
			va_end(argList);
			std::cout << msgString << std::endl;
		}
	}

	void Log::Console(Utils::CodeLocation location, char* msgFormat, ...)
	{
		if (SL_DEBUG_ENABLE)
		{
			va_list argList;
			va_start(argList, msgFormat);
			std::string msgString = Utils::StringUtil::FormatArguments(msgFormat, argList);
			va_end(argList);
			msgString.append("    <-- ");
			msgString.append(location.ToString());
			std::cout << msgString << std::endl;
		}
	}

	void Log::WriteFile(const char* msgFormat, ...)
	{
		if (m_osFile.is_open())
		{
			va_list argList;
			va_start(argList, msgFormat);
			std::string msgString = Utils::StringUtil::FormatArguments(msgFormat, argList);
			va_end(argList);

			m_osFile << msgString << std::endl;
		}
	}

	void Log::WriteFile(Utils::CodeLocation location, char* msgFormat, ...)
	{
		if (m_osFile.is_open())
		{
			va_list argList;
			va_start(argList, msgFormat);
			std::string msgString = Utils::StringUtil::FormatArguments(msgFormat, argList);
			va_end(argList);
			msgString.append("    <-- ");
			msgString.append(location.ToString());

			m_osFile << msgString << std::endl;
		}
	}
}