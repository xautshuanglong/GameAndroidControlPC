#pragma once

#include "../GenericDefines.h"
#include <string>

namespace Shuanglong::Algorithm
{
    class GENERIC_EXPORT MessageDigestAbstract
    {
    public:
        MessageDigestAbstract();
        virtual ~MessageDigestAbstract();

        virtual void Update(std::string &inString) = 0;
        virtual void Update(std::ifstream &inFileStream) = 0;
        virtual void Update(const char* inBuffer, int inLength) = 0;
        virtual std::string FinalDigest() = 0;
    };
}

