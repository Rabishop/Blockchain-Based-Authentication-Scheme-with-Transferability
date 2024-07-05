/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) [2024] [JIN XIUSHU]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void print_bytes(const unsigned char* bytes, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", bytes[i]);
    }
    printf("\n");
}

void string_to_bytes(const char* str, unsigned char* bytes, size_t len) {
    for (size_t i = 0; i < len; i++) {
        sscanf(&str[i * 2], "%2hhx", &bytes[i]);
    }
}

int main() {
    const char* ethereum_address = "YOUR_ETHEREUM_ADDRESS_HERE";
    size_t address_len = strlen(ethereum_address);
    
    const char* proxy_verify_key_str = "YOUR_PROXY_VERIFY_KEY_IN_HEX";
    unsigned char proxy_verify_key[32];
    string_to_bytes(proxy_verify_key_str, proxy_verify_key, 32);

    unsigned char nonce = 0;
    
    unsigned char combined[1 + address_len];
    SHA256_CTX sha256;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    while (1) {
        combined[0] = nonce;
        memcpy(combined + 1, ethereum_address, address_len);

        SHA256_Init(&sha256);
        SHA256_Update(&sha256, combined, sizeof(combined));
        SHA256_Final(hash, &sha256);

        if (memcmp(hash, proxy_verify_key, 32) == 0) {
            printf("Match found!\n");
            printf("Nonce: %02x\n", nonce);
            printf("Address: %s\n", ethereum_address);
            printf("Hash: ");
            print_bytes(hash, 32);
            break;
        }

        nonce++;
    }

    return 0;
}