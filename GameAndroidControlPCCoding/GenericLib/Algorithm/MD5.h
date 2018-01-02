#pragma once

#include "../GenericDefines.h"

namespace Shuanglong::Algorithm
{
    typedef unsigned char byte;
    typedef unsigned long ulong;

    class GENERIC_EXPORT MD5
    {
    private:
        static const byte PADDING[64];
        static const char HEX[16];
        static const size_t BUFFER_SIZE = 1024;

    public:
        MD5();
        ~MD5();

        std::string DDChangeHex(int a);
    };
}
