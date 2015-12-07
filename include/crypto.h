#ifndef CRYPTO_H
#define CRYPTO_H

#include <gcrypt.h>
#include <string>

namespace crypto
{

    class Crypto
    {
        private:
            std::string mKey;
            gcry_cipher_hd_t cipher;

            bool crypt_init();
            bool setIniVector(char *iniVector);

        public:
            Crypto(std::string key);
            char* encrypt(std::string buffer);
            char* decrypt(char *buffer);

    };
}
#endif
