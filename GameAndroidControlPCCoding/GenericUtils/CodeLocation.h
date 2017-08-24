#pragma once
#pragma warning(disable:4251)// 屏蔽导出模板类引发的警告(简单粗暴)

#include "GenericDefines.h"

#include <sstream>
#include <string>

#define SL_CODELOCATION Shuanglong::Utils::CodeLocation(__FILE__,__FUNCTION__,__LINE__)
#define SL_CODELOCATION_STRING Shuanglong::Utils::CodeLocation(__FILE__,__FUNCTION__,__LINE__).ToString()

namespace Shuanglong::Utils
{
    class GENERIC_EXPORT CodeLocation
    {
    private:
        std::string m_strFileName;// 源文件名(含绝对路径)
        std::string m_strShortFileName;
        std::string m_strFuncName;// 函数名
        int m_nLineNumber;     // 行号

    public:
        CodeLocation(char* fileName, char* funcName, int lineNumber);
        ~CodeLocation();

        int GetLineNumber();
        std::string GetFileName();
        std::string GetShortFileName();
        std::string GetShortClassName();
        std::string GetFuncName();
        std::string GetFullFuncName();
        std::string ToString();
    };
}
