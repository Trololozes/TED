#ifndef CRYPTO_H
#define CRYPTO_H

#include <gcrypt.h>
#include <string>

namespace crypto
{

    class Crypto
    {
        private:
            char* mKey;
            char* mBuffer;
            bool mStatus;
            gcry_cipher_hd_t mCipher;

            bool crypt_init();
            bool aes_init();
            void aes_destroy();

        public:
            Crypto();
            ~Crypto();
            char* encrypt(char const *buffer);
            char* decrypt(char const *buffer);
            bool status();
            void setKey(char *key);

    };
}
#endif
