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
            bool saveFile(char const *fileName);
            bool readFile(char const *fileName);
    };
}
#endif
