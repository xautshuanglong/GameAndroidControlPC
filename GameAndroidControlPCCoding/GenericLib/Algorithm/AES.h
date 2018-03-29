#pragma once

#include "../GenericDefines.h"
#include "CryptogramAbstract.h"

namespace Shuanglong
{
    namespace Algorithm
    {
        class GENERIC_EXPORT AES : public CryptogramAbstract
        {
        public:
            AES();
            virtual ~AES();

            virtual void Encrypt(void *pCleartext, long textLength) override;
            virtual void Decrypt(void *pCiphertext, long textLength) override;

            void Test();
        };
    }
}
