#include "stdafx.h"
#include "MD5Test.h"
#include <Algorithm/MD5.h>

using namespace Shuanglong::Algorithm;

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
        MD5 md5Test;
    }
}
