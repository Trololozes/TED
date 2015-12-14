/*
 *  Copyright (C) 2015  Carlos Millett
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gcrypt.h>
#include <fstream>
#include <cstdio>
#include <cstring>

#include "crypto.h"

namespace crypto
{

    AES::AES()
    {
        mKey = NULL;
        mBuffer = NULL;
        mStatus = crypt_init();
    }

    AES::~AES()
    {
        if( ! mKey )
            delete[] mKey;

        if( ! mBuffer )
            delete[] mBuffer;

        gcry_control(GCRYCTL_TERM_SECMEM);
    }

    bool AES::crypt_init()
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

    bool AES::aes_init()
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

    void AES::aes_destroy()
    {
        gcry_cipher_close(mCipher);
    }

    bool AES::status()
    {
        return mStatus;
    }

    void AES::setKey(char const *key)
    {
        mKey = new char[ strlen(key) + 1 ];
        strncpy(mKey, key, strlen(key)+1);

        return;
    }

    void AES::setBuffer(char const *buffer, size_t size)
    {
        mBufSize = size + 1;
        mBuffer = new char[mBufSize];

        strncpy(mBuffer, buffer, mBufSize);

        return;
    }

    char* AES::getBuffer()
    {
        return mBuffer;
    }

    bool AES::encrypt()
    {
        if( ! aes_init() )
            return false;

        gcry_cipher_encrypt(
            mCipher,
            mBuffer,
            mBufSize,
            NULL,
            0
        );

        aes_destroy();

        return true;
    }

    bool AES::decrypt()
    {
        if( ! aes_init() )
            return false;

        gcry_cipher_decrypt(
            mCipher,
            mBuffer,
            mBufSize,
            NULL,
            0
        );

        aes_destroy();

        return true;
    }

    void AES::saveFile(char const *fileName)
    {
        std::ofstream file;

        file.open(fileName, std::ios::binary);

        file.write(mBuffer, mBufSize);

        file.close();

        return;
    }

    void AES::readFile(char const *fileName)
    {
        std::ifstream file;

        file.open(fileName, std::ios::binary);

        file.seekg(0, file.end);
        mBufSize = file.tellg();
        file.seekg(0, file.beg);

        mBuffer = new char[mBufSize];
        file.read(mBuffer, mBufSize);

        file.close();

        return;
    }
}
