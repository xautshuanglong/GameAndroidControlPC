#include "StringUtil.h"

#include <Windows.h>
#include <iterator>
#include <codecvt>
#include <algorithm>

namespace Shuanglong::Utils
{
    std::string StringUtil::FormatString(const char* format, ...)
    {
        va_list argList;
        va_start(argList, format);
        std::string retString = FormatArguments(format, argList);
        va_end(argList);

        return retString;
    }

    std::string StringUtil::FormatArguments(const char* format, va_list argList)
    {
        std::string retString;
        char buffer[SL_STRINGUTIL_BUFFERLEN];
        _vsnprintf_s(buffer, SL_STRINGUTIL_BUFFERLEN, _TRUNCATE, format, argList);
        retString = buffer;

        return retString;
    }

    std::wstring StringUtil::FormatWString(const wchar_t* wFormat, ...)
    {
        va_list argList;
        va_start(argList, wFormat);
        std::wstring retString = FormatArgumentsW(wFormat, argList);
        va_end(argList);

        return retString;
    }

    std::wstring StringUtil::FormatArgumentsW(const wchar_t* wFormat, va_list argList)
    {
        std::wstring retString;
        wchar_t buffer[SL_STRINGUTIL_BUFFERLEN];
        _vsnwprintf_s(buffer, SL_STRINGUTIL_BUFFERLEN, _TRUNCATE, wFormat, argList);
        retString = buffer;

        return retString;
    }

    std::string StringUtil::Trim(const std::string& original)
    {
        static const char* whiteSpace = " \t\r\n";
        if (original.empty() || original.length() == 0)
        {
            return original;
        }
        std::string::size_type begin = original.find_first_not_of(whiteSpace);
        if (begin == std::string::npos)
        {
            return "";
        }
        std::string::size_type end = original.find_last_not_of(whiteSpace);
        return std::string(original, begin, end - begin + 1);
    }

    std::wstring StringUtil::TrimW(const std::wstring& original)
    {
        static const wchar_t* whiteSpace = L" \t\r\n";
        if (original.empty() || original.length() == 0)
        {
            return original;
        }
        std::string::size_type begin = original.find_first_not_of(whiteSpace);
        if (begin == std::string::npos)
        {
            return L"";
        }
        std::wstring::size_type end = original.find_last_not_of(whiteSpace);
        return std::wstring(original, begin, end - begin + 1);
    }

    unsigned int StringUtil::Split(std::vector<std::string>& v, std::string s, char delimiter, unsigned int maxSegments /* = INT_MAX */)
    {
        unsigned int i = 0;
        std::string::size_type left = 0, right = 0;
        v.clear();
        std::back_insert_iterator<std::vector<std::string>> it(v);
        for (i = 1; i < maxSegments; i++)
        {
            right = s.find(delimiter, left);
            if (right == std::string::npos)
            {
                break;
            }
            *it++ = s.substr(left, right - left);
            left = right + 1;
        }
        *it++ = s.substr(left);
        return i;
    }

    unsigned int StringUtil::SplitW(std::vector<std::wstring>& v, std::wstring s, wchar_t delimiter, unsigned int maxSegments /* = INT_MAX */)
    {
        unsigned int i = 0;
        std::wstring::size_type left = 0, right = 0;
        v.clear();
        std::back_insert_iterator<std::vector<std::wstring>> it(v);
        for (i = 1; i < maxSegments; i++)
        {
            right = s.find(delimiter, left);
            if (right == std::wstring::npos)
            {
                break;
            }
            *it++ = s.substr(left, right - left);
            left = right + 1;
        }
        *it++ = s.substr(left);
        return i;
    }

    std::wstring StringUtil::StringToWStringAPI(const std::string& originalStr)
    {
        wchar_t* pwChar = nullptr;
        std::wstring retString = L"";
        LPCSTR lpStr = originalStr.c_str();
        int nLen = MultiByteToWideChar(CP_ACP, 0, lpStr, -1, NULL, 0);
        if (nLen == 0)
        {
            return std::wstring(L"");
        }

        try
        {
            pwChar = new wchar_t[nLen];
        }
        catch (const std::bad_alloc& e)
        {
            e.what();
            return std::wstring(L"");
        }

        MultiByteToWideChar(CP_ACP, 0, lpStr, -1, pwChar, nLen);
        retString = pwChar;
        delete[] pwChar;

        return retString;
    }

    std::string StringUtil::WStringToStringAPI(const std::wstring& originalStr)
    {
        std::string retString = "";
        char* pChar = nullptr;
        LPCWSTR lpwStr = originalStr.c_str();
        int nLen = WideCharToMultiByte(CP_ACP, 0, lpwStr, -1, NULL, 0, NULL, NULL);
        if (nLen == 0)
        {
            return std::string("");
        }

        try
        {
            pChar = new char[nLen];
        }
        catch (const std::bad_alloc& e)
        {
            e.what();
            return std::string("");
        }

        WideCharToMultiByte(CP_ACP, 0, lpwStr, -1, pChar, nLen, NULL, NULL);
        retString = pChar;
        delete[] pChar;

        return retString;
    }

    std::string StringUtil::WStringToString(const std::wstring& originalStr)
    {
        std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> cvtAnsi(new std::codecvt<wchar_t, char, std::mbstate_t>("chs"));
        std::string retString = cvtAnsi.to_bytes(originalStr);

        // UTF-8 ? UNICODE
        //std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
        //std::wstring tempString = convert.from_bytes("\xe4\xb8\xad\xe6\x96\x87");
        //std::wcout << tempString << std::endl;

        return retString;
    }

    std::wstring StringUtil::StringToWString(const std::string& originalStr)
    {
        std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> cvtAnsi(new std::codecvt<wchar_t, char, std::mbstate_t>("chs"));
        std::wstring retString = cvtAnsi.from_bytes(originalStr);

        return retString;
    }

    std::string StringUtil::BoolToString(bool boolValue, bool bUppercase /* = false */)
    {
        std::string retValue = "false";
        if (boolValue)
        {
            retValue = "true";
        }

        if (bUppercase)
        {
            std::transform(retValue.begin(), retValue.end(), retValue.begin(), toupper);
        }

        return retValue;
    }

    /************************************************************************\
        Description: 将传入的字节串（可能含有不可见字符）
        转换成十六进制表示的字符串（不插入分隔符）
        Arguments  :
        inBuffer --> 需要转换的字节串
        inLength --> 传入字节串的长度（不含终结符）
        bUpperCase --> 指明字母用大小还是小写方式返回
    \************************************************************************/
    std::string StringUtil::GetHexString(const char* inBuffer, size_t inLength, bool bUpperCase /* = true */)
    {
        std::string retString = "";
        for (size_t i = 0; i < inLength; ++i)
        {
            retString += GetHexChar(inBuffer[i] >> 4 & 0x0F, bUpperCase);
            retString += GetHexChar(inBuffer[i] & 0x0F, bUpperCase);
        }

        return retString;
    }

    /************************************************************************\
        Description: 将传入的字节串（可能含有不可见字符）
        转换成十六进制表示的字符串（可插入前缀及后缀）
        Arguments  :
        inBuffer   --> 需要转换的字节串
        inLength   --> 传入字节串的长度（不含终结符）
        prefix     --> 每个十六进制前面的符号
        postfix    --> 每个十六进制后面的符号
        bUpperCase --> 指明字母用大小还是小写方式返回
    \************************************************************************/
    std::string StringUtil::GetHexString(const char* inBuffer, size_t inLength, const char* prefix, const char* postfix, bool bUpperCase /* = true */)
    {
        std::string retString = "";
        for (size_t i = 0; i < inLength; ++i)
        {
            retString += prefix;
            retString += GetHexChar(inBuffer[i] >> 4 & 0x0F, bUpperCase);
            retString += GetHexChar(inBuffer[i] & 0x0F, bUpperCase);
            retString += postfix;
        }

        return retString;
    }

    /************************************************************************\
    Description: 将单个字节转成字符
    Arguments  :
    charByte --> 需要转化的字节值
    bUpperCase --> 指明字母用大小还是小写方式返回
    \************************************************************************/
    char StringUtil::GetHexChar(const char charByte, bool bUpperCase)
    {
        char startChar = 'A';
        char retChar = '\0';
        if (charByte < 10)
        {
            retChar = '0' + charByte;
        }
        else
        {
            if (!bUpperCase)
            {
                startChar = 'a';
            }
            retChar = startChar - 10 + charByte;
        }

        return retChar;
    }
}

