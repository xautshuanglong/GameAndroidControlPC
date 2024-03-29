#include "CodeLocation.h"

#include <iostream>

namespace Shuanglong::Utils
{
    CodeLocation::CodeLocation(const char* fileName, const char* funcName, int lineNumber)
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
        size_t index = std::string::npos;
        m_strShortFileName = m_strFileName;

        index = m_strFileName.find_last_of('\\');
        if (index != std::string::npos)
        {
            m_strShortFileName.erase(0, index + 1);
        }

        return m_strShortFileName;
    }

    std::string CodeLocation::GetShortClassName()
    {
        std::string className("");
        size_t index = m_strFuncName.find_last_of(":");
        if (index != std::string::npos)
        {
            className = m_strFuncName.substr(0, index - 1);
        }
        index = className.find_last_of(":");
        if (index != std::string::npos)
        {
            className.erase(0, index + 1);
        }

        return className;
    }

    std::string CodeLocation::GetFunctionName()
    {
        std::string funcName = m_strFuncName;
        size_t index = funcName.find_last_of(":");
        if (index != std::string::npos)
        {
            funcName.erase(0, index + 1);
        }

        return funcName;
    }

    std::string CodeLocation::GetFunctionNameFull()
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
