#include <gcrypt.h>
#include <string>
#include <cstring>

#include "crypto.h"

namespace crypto
{

    Crypto::Crypto()
    {
        mKey = NULL;
        mBuffer = NULL;
        mStatus = crypt_init();
    }

    Crypto::~Crypto()
    {
        if( ! mKey )
            delete[] mKey;

        if( ! mBuffer )
            delete[] mBuffer;
    }

    bool Crypto::crypt_init()
    {
        gcry_error_t error;

        if( ! gcry_check_version(GCRYPT_VERSION) )
            return false;

        error = gcry_control(GCRYCTL_SUSPEND_SECMEM_WARN);
        error |= gcry_control(GCRYCTL_INIT_SECMEM, 16384, 0);
        error |= gcry_control(GCRYCTL_RESUME_SECMEM_WARN);
        error |= gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

        if( error )
            return false;

        return true;
    }

    bool Crypto::aes_init()
    {
        gcry_error_t error;
        size_t aesKeyLength = gcry_cipher_get_algo_keylen(GCRY_CIPHER_AES128);
        size_t aesBlkLength = gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES128);
        char hash[aesKeyLength];

        size_t keyLength = mKey ? strlen(mKey) : 0;
        if( keyLength == 0 )
            return false;

        error = gcry_cipher_open(
            &mCipher,
            GCRY_CIPHER_AES128,
            GCRY_CIPHER_MODE_CFB,
            0
        );
        if( error )
            return false;

        gcry_md_hash_buffer(GCRY_MD_MD5, hash, mKey, keyLength);

        error = gcry_cipher_setkey(mCipher, hash, aesKeyLength);
        if( error )
            return false;

        error = gcry_cipher_setiv(mCipher, hash, aesBlkLength);
        if( error )
            return false;

        return true;
    }

    void Crypto::aes_destroy()
    {
        gcry_cipher_close(mCipher);
    }

    char* Crypto::encrypt(char const *buffer)
    {
        size_t size = std::strlen(buffer) + 1;
        mBuffer = new char[size];

        if( ! aes_init() )
        {
            delete[] mBuffer;
            return (mBuffer = NULL);
        }

        gcry_cipher_encrypt(
            mCipher,
            mBuffer,
            size - 1,
            buffer,
            size - 1
        );

        aes_destroy();

        return mBuffer;
    }

    char* Crypto::decrypt(char const *buffer)
    {
        size_t size = std::strlen(buffer) + 1;
        mBuffer = new char[size];

        if( ! aes_init() )
        {
            delete[] mBuffer;
            return (mBuffer = NULL);
        }

        gcry_cipher_decrypt(
            mCipher,
            mBuffer,
            size - 1,
            buffer,
            size - 1
        );

        aes_destroy();

        return mBuffer;
    }

    bool Crypto::status()
    {
        return mStatus;
    }

    void Crypto::setKey(char *key)
    {
        mKey = new char[ strlen(key) + 1 ];
        strncpy(mKey, key, strlen(key)+1);
    }
}
