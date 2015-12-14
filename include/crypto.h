#ifndef CRYPTO_H
#define CRYPTO_H

#include <gcrypt.h>

namespace crypto
{

    class AES
    {
        private:
            char* mKey;
            char* mBuffer;
            size_t mBufSize;
            bool mStatus;
            gcry_cipher_hd_t mCipher;

        private:
            bool crypt_init();
            bool aes_init();
            void aes_destroy();

        public:
            AES();
            ~AES();
            bool status();
            void setKey(char const *key);
            void setBuffer(char const *buffer, size_t size);
            char* getBuffer();
            bool encrypt();
            bool decrypt();
            void saveFile(char const *fileName);
            void readFile(char const *fileName);
    };
}
#endif
