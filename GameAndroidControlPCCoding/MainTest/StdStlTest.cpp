#include "stdafx.h"
#include "StdStlTest.h"

namespace Shuanglong::Test
{
    StdStlTest* StdStlTest::mpInstance = nullptr;
    StdStlTest::SingleHelpper StdStlTest::mHelpper;

    StdStlTest::SingleHelpper::SingleHelpper()
    {
        mpInstance = new StdStlTest();
    }

    StdStlTest::SingleHelpper::~SingleHelpper()
    {
        if (mpInstance != nullptr)
        {
            delete mpInstance;
            mpInstance = nullptr;
        }
    }

    StdStlTest::StdStlTest()
    {}

    StdStlTest::~StdStlTest()
    {}

    void StdStlTest::Entry()
    {
        std::cout << "----------------------------- StdStl Testing -----------------------------" << std::endl;
        mpInstance->mpLog = Log::GetInstance();

        //mpInstance->StdListTestUnique();
        //mpInstance->StdListTestFind();
    }

    void StdStlTest::StdListTestUnique()
    {
        std::cout << "----------------------------- StdStlTest::StdListTestUnique() -----------------------------" << std::endl;

        std::stringstream ss;
        std::list<int> intList = { 1, 2, 2, 3, 3, 2, 1, 1, 2 };

        for (auto val : intList)
        {
            ss << " " << val;
        }
        mpLog->Console(SL_CODELOCATION, "Initialized data: %s", ss.str().c_str());

        ss.clear();       // 仅清除错误标记
        ss.str("");       // 清空字符串
        intList.unique(); // 注意：仅保留相邻且相同分组中的第一个元素。
        for (auto val : intList)
        {
            ss << " " << val;
        }
        mpLog->Console(SL_CODELOCATION, "After unique data: %s", ss.str().c_str());
    }

    void StdStlTest::StdListTestFind()
    {
        std::cout << "----------------------------- StdStlTest::StdListTestFind() -----------------------------" << std::endl;
        std::stringstream ss;
        
        //std::list<int> intList = { 1, 2, 2, 3, 3, 2, 1, 1, 2 };
        std::list<int> intList = { 0, 11, 22, 33, 44, 55, 66, 77, 88, 99 };
        for (auto val : intList)
        {
            ss << " " << val;
        }
        mpLog->Console(SL_CODELOCATION, "Initialized data: %s", ss.str().c_str());

        std::list<int>::iterator targetInt = std::find(intList.begin(), intList.end(), 99);
        if (targetInt != intList.end())
        {
            mpLog->Console(SL_CODELOCATION, "tagetInt=%d", *targetInt);
        }
        else
        {
            mpLog->Console(SL_CODELOCATION, "Not found.");
        }

        int index = 0;
        for (auto temp=intList.begin(); temp!=intList.end(); ++temp)
        {
            if (temp == targetInt)
            {
                mpLog->Console(SL_CODELOCATION, "bingo at index: %d", index);
                break;
            }
            ++index;
            if (index == intList.size())
            {
                mpLog->Console(SL_CODELOCATION, "target is not exist.");
            }
        }
    }
}
