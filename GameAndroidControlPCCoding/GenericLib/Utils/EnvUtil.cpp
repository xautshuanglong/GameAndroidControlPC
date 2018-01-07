#include "EnvUtil.h"

namespace Shuanglong::Utils
{
    EnvUtil::EnvUtil()
    {}

    EnvUtil::~EnvUtil()
    {}

    bool EnvUtil::IsBigEndian()
    {
        bool retFlag = false;
        union EndianTest
        {
            int intVaule;
            char bytes[4];
        };

        EndianTest endian = { 0 };
        endian.intVaule = 0x12345678;
        if (endian.bytes[0] == 0x12)
        {
            retFlag = true;
        }
        return retFlag;
    }

    bool EnvUtil::IsLittleEndian()
    {
        bool retFlag = false;
        int endianTest = 0x12345678;
        char *pLittle = (char*)&endianTest;
        if (*pLittle == 0x78)
        {
            retFlag = true;
        }
        return retFlag;
    }
}
