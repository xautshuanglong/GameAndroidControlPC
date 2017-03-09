#include "stdafx.h"
#include "CodeLocation.h"

#include <iostream>

namespace ShuangLong
{
	CodeLocation::CodeLocation(char* fileName, char* funcName, int lineNumber)
	{
		m_strFileName = fileName;
		m_strFuncName = funcName;
		m_nLineNumber = lineNumber;
	}

	CodeLocation::~CodeLocation()
	{
		//std::cout << "CodeLocation::~CodeLocation()" << std::endl;
	}

	int CodeLocation::GetLineNumber()
	{
		return m_nLineNumber;
	}

	std::string CodeLocation::GetFileName()
	{
		return m_strFileName;
	}

	std::string CodeLocation::GetShortFileName()
	{
		if (m_strShortFileName.empty())
		{
			size_t index = m_strFileName.find_last_of('\\');
			if (index != std::string::npos)
			{
				m_strShortFileName = m_strFileName.substr(index+1);
			}
			else
			{
				m_strShortFileName = m_strFileName;
			}
		}

		return m_strShortFileName;
	}

	std::string CodeLocation::GetShortClassName()
	{
		std::string className("");
		std::cout << m_strFuncName << std::endl;
		size_t index = m_strFuncName.find_last_of(":");
		std::cout << "index=" << index << std::endl;
		if (index != std::string::npos)
		{
			className = m_strFuncName.substr(0, index-1);
		}
		index = className.find_last_of(":");
		if (index != std::string::npos)
		{
			className.erase(0, index);
		}

		return className;
	}

	std::string CodeLocation::GetFuncName()
	{
		return m_strFuncName;
	}

	std::string CodeLocation::GetFullFuncName()
	{
		return m_strFuncName;
	}

	std::string CodeLocation::ToString()
	{
		std::ostringstream oss;
		oss << m_nLineNumber;
		std::string retString = "[ ";
		retString.append(m_strFuncName);
		retString.append(" ");
		retString.append(GetShortFileName());
		retString.append(":");
		retString.append(oss.str());
		retString.append(" ]");

		return retString;
	}
}
