#include <iostream>
#include <StringUtil.h>

#include "StringUtilTest.h"

namespace ShuangLong
{
	StringUtilTest* StringUtilTest::mpInstance = nullptr;

	StringUtilTest::StringUtilTest()
	{
	}


	StringUtilTest::~StringUtilTest()
	{
	}

	void StringUtilTest::Entry()
	{
		mpInstance = new StringUtilTest();
		mpInstance->mpLog = Log::GetInstance();

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

	void StringUtilTest::StringUtilTest_Trim()
	{
		std::cout << std::endl << "-------------------------------- StringUtilTest_Trim --------------------------------" << std::endl;
		std::string test = "\t sdfsdf  sdfsdf  \t";
		std::cout << "BEGIN" << test << "END" << std::endl;
		std::cout << "BEGIN:" << ShuangLong::Utils::StringUtil::Trim(test) << "END" << std::endl;
	}

	void StringUtilTest::StringUtilTest_TrimW()
	{
		std::cout << std::endl << "-------------------------------- StringUtilTest_TrimW --------------------------------" << std::endl;
		std::wstring wtest = L"\t sdfsdf  sdfsdf  \t";
		std::wcout << "BEGIN" << wtest << "END" << std::endl;
		std::wcout << "BEGIN:" << ShuangLong::Utils::StringUtil::TrimW(wtest) << "END" << std::endl;
	}

	void StringUtilTest::StringUtilTest_Split()
	{
		std::cout << std::endl << "-------------------------------- StringUtilTest_Split --------------------------------" << std::endl;
		std::vector<std::string> nameVector;
		std::string nameString = "zhangsan,lisi,wanger,mazi";
		unsigned int count = ShuangLong::Utils::StringUtil::Split(nameVector, nameString, ',');

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
		unsigned int count = ShuangLong::Utils::StringUtil::SplitW(nameVector, nameString, L',');

		//mpLog->Console(SL_CODELOCATION, "count=%u  nameString=%s", count, std::string(nameString.begin(), nameString.end()).c_str());
		mpLog->Console(SL_CODELOCATION, "count=%u  nameString=%s", count, ShuangLong::Utils::StringUtil::WStringToStringAPI(nameString).c_str());

		std::vector<std::wstring>::iterator it;
		int index = 0;
		for (it = nameVector.begin(); it != nameVector.end(); it++)
		{
			//mpLog->Console("name[%d] = %s", index++, std::string(it->begin(), it->end()).c_str());
			mpLog->Console("name[%d] = %s", index++, ShuangLong::Utils::StringUtil::WStringToStringAPI(it->c_str()).c_str());
		}
	}

	void StringUtilTest::StringUtilTest_StringToWStringAPI()
	{
		std::cout << std::endl << "-------------------------------- StringUtilTest_StringToWStringAPI --------------------------------" << std::endl;
		std::string testStr = "×ª»»²âÊÔ£ºConvert string to wstring";
		std::cout << "String: " << testStr << std::endl;
		std::wcout << L"WString: " << ShuangLong::Utils::StringUtil::StringToWStringAPI(testStr) << std::endl;
	}

	void StringUtilTest::StringUtilTest_WStringToStringAPI()
	{
		std::cout << std::endl << "-------------------------------- StringUtilTest_WStringToStringAPI --------------------------------" << std::endl;
		std::wstring testWStr = L"×ª»»²âÊÔ£ºConvert wstring to string";
		std::wcout << L"WString: " << testWStr << std::endl;
		std::cout << "String: " << ShuangLong::Utils::StringUtil::WStringToStringAPI(testWStr) << std::endl;
	}

	void StringUtilTest::StringUtilTest_WStringToString()
	{
		std::cout << std::endl << "-------------------------------- StringUtilTest_WStringToString --------------------------------" << std::endl;
		std::wstring testWStr = L"×ª»»²âÊÔ£ºConvert wstring to string";
		std::wcout << L"WString: " << testWStr << std::endl;
		std::cout << "String: " << ShuangLong::Utils::StringUtil::WStringToString(testWStr) << std::endl;
	}

	void StringUtilTest::StringUtilTest_StringToWString()
	{
		std::cout << std::endl << "-------------------------------- StringUtilTest_StringToWString --------------------------------" << std::endl;
		std::string testStr = "×ª»»²âÊÔ£ºConvert wstring to string";
		std::cout << "String: " << testStr << std::endl;
		std::wcout << L"WString: " << ShuangLong::Utils::StringUtil::StringToWString(testStr) << std::endl;
	}
}
