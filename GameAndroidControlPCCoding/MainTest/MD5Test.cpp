#include "stdafx.h"
#include "MD5Test.h"

namespace Shuanglong::Test
{
    MD5Test::MD5Test()
    {}


    MD5Test::~MD5Test()
    {}

    MD5Test* MD5Test::GetInstance()
    {
        static MD5Test instance;
        return &instance;
    }

    void MD5Test::Entry()
    {
        GetInstance()->CaculateMD5Test();
    }

    void MD5Test::Exit()
    {
        std::cout << "---------------------------------- MD5Test ----------------------------------" << std::endl;
        ;
    }

    void MD5Test::CaculateMD5Test()
    {
        int x = 0x80000002;
        int bitCnt = 1;
        int res = x >> (bitCnt);

        printf_s("0x%08X >> 0x%08X(%d) = 0x%08X\n", x, bitCnt, bitCnt, res);
    }
}
