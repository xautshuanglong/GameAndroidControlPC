#pragma once

#include "../GenericDefines.h"
#include "MessageDigestAbstract.h"

namespace Shuanglong::Algorithm
{
    typedef unsigned char byte;
    typedef unsigned long ulong;

    class GENERIC_EXPORT MD5 : public MessageDigestAbstract
    {
    private:
        static const byte PADDING[64];
        static const char HEX[16];
        static const size_t BUFFER_SIZE = 1024;

    public:
        MD5();
        ~MD5();

        virtual void Update(std::string &inString);
        virtual void Update(std::ifstream &inFileStream);
        virtual void Update(const char* inBuffer, int inLength);
        virtual std::string FinalDigest();

    private:
        virtual bool IsLittleEndian();
        std::string ChangeToHex(int a);
    };
}
