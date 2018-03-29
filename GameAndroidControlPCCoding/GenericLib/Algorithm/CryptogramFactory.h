#pragma once

namespace Shuanglong
{
    namespace Algorithm
    {
        enum class EncryptionType
        {
            ENCRYPTION_AES
        };

        class CryptogramFactory
        {
        public:
            ~CryptogramFactory();
            void Encrypt(EncryptionType encryptionType, void *pClearText, long textLength);
            void Decrypt(EncryptionType encryptionType, void *pCipherText, long textLength);

        private:
            CryptogramFactory();
        };
    }
}
