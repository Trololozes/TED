#include <gcrypt.h>
#include <string>
#include <cstring>

#include "crypto.h"

namespace crypto
{

    Crypto::Crypto(std::string key)
    {
        mKey = key;
    }

    bool Crypto::crypt_init()
    {
        gcry_error_t error;
        size_t keyLength = gcry_cipher_get_algo_keylen(GCRY_CIPHER_AES128);

        error = gcry_cipher_open(
            &cipher,
            GCRY_CIPHER_AES128,     // Algoritmo
            GCRY_CIPHER_MODE_CBC,   // Modo de operacao
            GCRY_CIPHER_SECURE      // Flags
        );
        if( error )
            return false;

        error = gcry_cipher_setkey(cipher, mKey.c_str(), keyLength);
        if( error )
            return false;

        return true;
    }

    bool Crypto::setIniVector(char *iniVector)
    {
        size_t blkLength = gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES128);

        if( gcry_cipher_setiv(cipher, iniVector, blkLength) )
            return false;

        return true;

    }

    char* Crypto::encrypt(std::string buffer)
    {
        size_t size = buffer.size() + 1;
        char *enc = new char[size];

        if( ! (crypt_init() && setIniVector((char*)"NotUnicorn")) )
            return NULL;

        memcpy(enc, buffer.c_str(), buffer.size());

        gcry_cipher_encrypt(
            cipher,
            enc,
            size - 1,
            NULL,       // Criptografa buffer
            0           // in-place
        );

        return enc;
    }

    char* Crypto::decrypt(char *buffer)
    {
        size_t size = std::strlen(buffer) + 1;
        char *dec = new char[size];

        if( ! (crypt_init() && setIniVector((char*)"NotUnicorn")) )
            return NULL;

        memcpy(dec, buffer, size);

        gcry_cipher_decrypt(
            cipher,
            dec,
            size - 1,
            NULL,       // Decriptografa buffer
            0           // in-place
        );

        return dec;
    }
}
