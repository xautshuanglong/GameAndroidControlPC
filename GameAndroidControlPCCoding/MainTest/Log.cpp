#include "Log.h"

#include <windows.h>

namespace ShuangLong
{
	//volatile bool Log::m_bInitFlag = false;
	//std::mutex Log::m_mutex;
	Log::Helpper Log::helpper;
	Log* Log::m_pInstance = nullptr;
	std::once_flag Log::m_instanceFlag;

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

	void Log::init()
	{
		m_pInstance = new Log();
	}

	Log* Log::GetInstance()
	{
		// 存在条件竞争，后来线程未必看得到先前线程创建的实例(用 std::once_flag  std::call_once 代替)
		//if (m_bInitFlag==false && m_pInstance==nullptr)
		//{
		//	//std::lock_guard<std::mutex> lock(m_mutex);
		//	m_mutex.lock();
		//	if (m_bInitFlag==false && m_pInstance==nullptr)
		//	{
		//		m_pInstance = new Log();
		//		m_bInitFlag = true;
		//	}
		//	m_mutex.unlock();
		//}
		std::call_once(m_instanceFlag, init);

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
			AddTimestamp(msgString);
			std::cout << msgString << std::endl;
		}
	}

	void Log::Console(CodeLocation location, char* msgFormat, ...)
	{
		if (SL_DEBUG_ENABLE)
		{
			va_list argList;
			va_start(argList, msgFormat);
			std::string msgString = Utils::StringUtil::FormatArguments(msgFormat, argList);
			va_end(argList);
			AddTimestamp(msgString);
			AddCodeLocation(msgString, location);
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
			AddTimestamp(msgString);
			m_osFile << msgString << std::endl;
		}
	}

	void Log::WriteFile(CodeLocation location, char* msgFormat, ...)
	{
		if (m_osFile.is_open())
		{
			va_list argList;
			va_start(argList, msgFormat);
			std::string msgString = Utils::StringUtil::FormatArguments(msgFormat, argList);
			va_end(argList);
			AddTimestamp(msgString);
			AddCodeLocation(msgString, location);
			m_osFile << msgString << std::endl;
		}
	}

	void Log::AddTimestamp(std::string& msgString)
	{
		std::string timeString = Utils::TimeUtil::GetSimpleTimestampString();
		timeString.append(" ");
		msgString.insert(0, timeString);
	}

	void Log::AddCodeLocation(std::string& msgString, CodeLocation& location)
	{
		//msgString.append("    <-- ");
		msgString.append("    ");
		msgString.append(location.ToString());
	}
}