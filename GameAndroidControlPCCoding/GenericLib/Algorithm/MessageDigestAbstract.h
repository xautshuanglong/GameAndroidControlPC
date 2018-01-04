#pragma once

#include <string>

namespace Shuanglong::Algorithm
{
    class MessageDigestAbstract
    {
    public:
        MessageDigestAbstract();
        virtual ~MessageDigestAbstract();

        virtual std::string Update(std::string inString) = 0;
        virtual std::string Update(const char* inBuffer, int inLength) = 0;
        virtual void Update(const char* inBuffer, int inLength, const char* outBuffer, int outLength) = 0;
        virtual std::string FinalDigest() = 0;
    };
}

