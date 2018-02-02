#pragma once
#include "../GenericDefines.h"

#include <vector>

#define SL_STRINGUTIL_BUFFERLEN 1024

namespace Shuanglong::Utils
{
    //************************************************************************\
    //    Author     : JiangChuanbiao
    //    Date       : 2018-2-1
    //    Description: ×Ö·û´®²Ù×÷¹¤¾ß
    //              1. ×Ö·û´®¸ñÊ½»¯£»
    //              2. ÌÞ³ý¿Õ×Ö·û" \t\r\n"£»
    //              3. ×Ö·û´®·Ö¸î£»
    //              4. ¿í×Ö½ÚÓë¶à×Ö½Ú»¥×ª¡£
    //************************************************************************/
    class GENERIC_EXPORT StringUtil
    {
    public:
        StringUtil() = delete;
        StringUtil(const StringUtil& originalObj) = delete;
        StringUtil(StringUtil&& originalObj) = delete;

    private:
        static char StringUtil::GetHexChar(const char charByte, bool bUpperCase);

    public:
        std::string static FormatString(const char* format, ...);
        std::wstring static FormatWString(const wchar_t* wFormat, ...);

        std::string static FormatArguments(const char* format, va_list argList);
        std::wstring static FormatArgumentsW(const wchar_t* wFormat, va_list argList);

        std::string static Trim(const std::string& original);
        std::wstring static TrimW(const std::wstring& original);

        unsigned int static Split(std::vector<std::string>& v, std::string s, char delimiter, unsigned int maxSegments = INT_MAX);
        unsigned int static SplitW(std::vector<std::wstring>& v, std::wstring s, wchar_t delimiter, unsigned int maxSegments = INT_MAX);

        std::wstring static StringToWStringAPI(const std::string& originalStr);
        std::string static WStringToStringAPI(const std::wstring& originalStr);

        std::string static WStringToString(const std::wstring& originalStr);
        std::wstring static StringToWString(const std::string& originalStr);

        static std::string BoolToString(bool boolValue, bool bUppercase = false);
        static std::string GetHexString(const char* inBuffer, size_t inLength, bool bUpperCase = true);
        static std::string GetHexString(const char* inBuffer, size_t inLength, const char* prefix, const char* postfix, bool bUpperCase = true);
    };
}
