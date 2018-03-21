#pragma once
#pragma warning(disable:4251)// ���ε���ģ���������ľ���(�򵥴ֱ�)

#include "../GenericDefines.h"

#include <sstream>
#include <string>

#define SL_CODE_LOCATION Shuanglong::Utils::CodeLocation(__FILE__,__FUNCTION__,__LINE__)
#define SL_CODE_LOCATION_STRING Shuanglong::Utils::CodeLocation(__FILE__,__FUNCTION__,__LINE__).ToString()

namespace Shuanglong
{
    namespace Utils
    {
        class GENERIC_EXPORT CodeLocation
        {
        private:
            std::string m_strFileName;       // Դ�ļ���(������·��)
            std::string m_strShortFileName;  // ���ļ���(�޾���·��)
            std::string m_strFuncName;       // ��������ȫ��  namespace::class::MemberFunction��
            int m_nLineNumber;               // �к�

        public:
            CodeLocation(char* fileName, char* funcName, int lineNumber);
            ~CodeLocation();

            int GetLineNumber();
            std::string GetFileName();
            std::string GetShortFileName();
            std::string GetShortClassName();
            std::string GetFunctionName();
            std::string GetFunctionNameFull();
            std::string ToString();
        };
    }
}
