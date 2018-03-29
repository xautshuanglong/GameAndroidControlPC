#pragma once

#include "../GenericDefines.h"

namespace Shuanglong
{
    namespace Algorithm
    {
        class GENERIC_EXPORT CryptogramAbstract
        {
        public:
            CryptogramAbstract();
            virtual ~CryptogramAbstract();

            virtual void Encrypt(void *pCleartext, long textLength) = 0;
            virtual void Decrypt(void *pCiphertext, long textLength) = 0;
        };
    }
}
