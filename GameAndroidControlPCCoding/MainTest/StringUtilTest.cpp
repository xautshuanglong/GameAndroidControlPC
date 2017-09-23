#include "stdafx.h"
#include "StringUtilTest.h"

#include <iostream>
#include <Utils/StringUtil.h>

//using namespace Shuanglong::Utils;

namespace Shuanglong::Test
{
    StringUtilTest* StringUtilTest::mpInstance = nullptr;

    StringUtilTest::StringUtilTest()
    {}


    StringUtilTest::~StringUtilTest()
    {}

    void StringUtilTest::Entry()
    {
        mpInstance = new StringUtilTest();
        mpInstance->mpLog = Log::GetInstance();

        mpInstance->StringUtilTest_FormateString();
        mpInstance->StringUtilTest_FormateWString();

        char charString[] = "charString_test";
        std::string stdString = "stdString_test";
        int intNum = 110;
        mpInstance->StringUtilTest_FormatArguments("charString=%s stdString=%s intNum=%d", charString, stdString.c_str(), intNum);

        wchar_t wcharString[] = L"wcharString_test";
        std::wstring stdWString = L"stdWString_test";
        mpInstance->StringUtilTest_FormatArgumentsW(L"wcharString=%s stdWString=%s intNum=%d", wcharString, stdWString.c_str(), intNum);

        mpInstance->StringUtilTest_Trim();
        mpInstance->StringUtilTest_TrimW();
        mpInstance->StringUtilTest_Split();
        mpInstance->StringUtilTest_SplitW();

        std::wcout.imbue(std::locale("chs"));

        mpInstance->StringUtilTest_StringToWStringAPI();
        mpInstance->StringUtilTest_WStringToStringAPI();
        mpInstance->StringUtilTest_WStringToString();
        mpInstance->StringUtilTest_StringToWString();
    }

    void StringUtilTest::StringUtilTest_FormateString()
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_FormateString --------------------------------" << std::endl;
        char charString[] = "charString_test";
        std::string stdString = "stdString_test";
        int intNum = 110;
        std::string retString = Utils::StringUtil::FormatString("charString=%s stdString=%s intNum=%d", charString, stdString.c_str(), intNum);
        mpLog->Console(SL_CODELOCATION, "StringUtil::FormatString: %s", retString.c_str());
    }

    void StringUtilTest::StringUtilTest_FormateWString()
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_FormateWString --------------------------------" << std::endl;
        wchar_t wcharString[] = L"wcharString_test";
        std::wstring stdWString = L"stdWString_test";
        int intNum = 110;
        std::wstring retString = Utils::StringUtil::FormatWString(L"wcharString=%s stdWString=%s intNum=%d", wcharString, stdWString.c_str(), intNum);
        std::wcout << "StringUtil::FormatWString: " << retString.c_str() << std::endl;
        mpLog->Console(SL_CODELOCATION, "StringUtil.FormatWString: %s", Utils::StringUtil::WStringToString(retString).c_str());
    }

    void StringUtilTest::StringUtilTest_FormatArguments(char *format, ...)
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_FormatArguments --------------------------------" << std::endl;
        va_list argList;
        va_start(argList, format);
        std::string retString = Utils::StringUtil::FormatArguments(format, argList);
        va_end(argList);
        std::cout << "StringUtil::FormatArguments " << retString.c_str() << std::endl;
    }

    void StringUtilTest::StringUtilTest_FormatArgumentsW(wchar_t *format, ...)
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_FormatArgumentsW --------------------------------" << std::endl;
        va_list argList;
        va_start(argList, format);
        std::wstring retString = Utils::StringUtil::FormatArgumentsW(format, argList);
        va_end(argList);
        std::wcout << "StringUtil::FormatArgumentsW " << retString.c_str() << std::endl;
    }

    void StringUtilTest::StringUtilTest_Trim()
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_Trim --------------------------------" << std::endl;
        std::string test = "\t sdfsdf  sdfsdf  \t";
        std::cout << "BEGIN" << test << "END" << std::endl;
        std::cout << "BEGIN:" << Shuanglong::Utils::StringUtil::Trim(test) << "END" << std::endl;
    }

    void StringUtilTest::StringUtilTest_TrimW()
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_TrimW --------------------------------" << std::endl;
        std::wstring wtest = L"\t sdfsdf  sdfsdf  \t";
        std::wcout << "BEGIN" << wtest << "END" << std::endl;
        std::wcout << "BEGIN:" << Shuanglong::Utils::StringUtil::TrimW(wtest) << "END" << std::endl;
    }

    void StringUtilTest::StringUtilTest_Split()
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_Split --------------------------------" << std::endl;
        std::vector<std::string> nameVector;
        std::string nameString = "zhangsan,lisi,wanger,mazi";
        unsigned int count = Shuanglong::Utils::StringUtil::Split(nameVector, nameString, ',');

        mpLog->Console(SL_CODELOCATION, "count=%u  nameString=%s", count, nameString.c_str());

        //for (int i = 0; i < count; i++)
        //{
        //	mpLog->Console("name[%d] = %s", i, nameVector[i].c_str());
        //}

        std::vector<std::string>::iterator it;
        int index = 0;
        for (it = nameVector.begin(); it != nameVector.end(); it++)
        {
            mpLog->Console("name[%d] = %s", index++, it->c_str());
        }
    }

    void StringUtilTest::StringUtilTest_SplitW()
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_SplitW --------------------------------" << std::endl;
        std::vector<std::wstring> nameVector;
        std::wstring nameString = L"zhangsan,lisi,wanger,mazi";
        unsigned int count = Shuanglong::Utils::StringUtil::SplitW(nameVector, nameString, L',');

        //mpLog->Console(SL_CODELOCATION, "count=%u  nameString=%s", count, std::string(nameString.begin(), nameString.end()).c_str());
        mpLog->Console(SL_CODELOCATION, "count=%u  nameString=%s", count, Shuanglong::Utils::StringUtil::WStringToStringAPI(nameString).c_str());

        std::vector<std::wstring>::iterator it;
        int index = 0;
        for (it = nameVector.begin(); it != nameVector.end(); it++)
        {
            //mpLog->Console("name[%d] = %s", index++, std::string(it->begin(), it->end()).c_str());
            mpLog->Console("name[%d] = %s", index++, Shuanglong::Utils::StringUtil::WStringToStringAPI(it->c_str()).c_str());
        }
    }

    void StringUtilTest::StringUtilTest_StringToWStringAPI()
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_StringToWStringAPI --------------------------------" << std::endl;
        std::string testStr = "×ª»»²âÊÔ£ºConvert string to wstring";
        std::cout << "String: " << testStr << std::endl;
        std::wcout << L"WString: " << Shuanglong::Utils::StringUtil::StringToWStringAPI(testStr) << std::endl;
    }

    void StringUtilTest::StringUtilTest_WStringToStringAPI()
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_WStringToStringAPI --------------------------------" << std::endl;
        std::wstring testWStr = L"×ª»»²âÊÔ£ºConvert wstring to string";
        std::wcout << L"WString: " << testWStr << std::endl;
        std::cout << "String: " << Shuanglong::Utils::StringUtil::WStringToStringAPI(testWStr) << std::endl;
    }

    void StringUtilTest::StringUtilTest_WStringToString()
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_WStringToString --------------------------------" << std::endl;
        std::wstring testWStr = L"×ª»»²âÊÔ£ºConvert wstring to string";
        std::wcout << L"WString: " << testWStr << std::endl;
        std::cout << "String: " << Shuanglong::Utils::StringUtil::WStringToString(testWStr) << std::endl;
    }

    void StringUtilTest::StringUtilTest_StringToWString()
    {
        std::cout << std::endl << "-------------------------------- StringUtilTest_StringToWString --------------------------------" << std::endl;
        std::string testStr = "×ª»»²âÊÔ£ºConvert wstring to string";
        std::cout << "String: " << testStr << std::endl;
        std::wcout << L"WString: " << Shuanglong::Utils::StringUtil::StringToWString(testStr) << std::endl;
    }
}

