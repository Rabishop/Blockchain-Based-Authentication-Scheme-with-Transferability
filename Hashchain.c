# #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define HASH_CHAIN_LENGTH 1000
#define HASH_LENGTH SHA256_DIGEST_LENGTH
#define MASTER_KEY_FILE "master_key.txt"
#define OUTPUT_FILE "hash_chain.txt"

void read_master_key(unsigned char *master_key, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open master key file");
        exit(EXIT_FAILURE);
    }
    fread(master_key, 1, HASH_LENGTH, file);
    fclose(file);
}

void sha256(const unsigned char *input, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, HASH_LENGTH);
    SHA256_Final(output, &sha256);
}

void generate_hash_chain(unsigned char hash_chain[HASH_CHAIN_LENGTH][HASH_LENGTH], unsigned char *master_key) {
    memcpy(hash_chain[0], master_key, HASH_LENGTH);
    for (int i = 1; i < HASH_CHAIN_LENGTH; i++) {
        sha256(hash_chain[i - 1], hash_chain[i]);
    }
}

void output_hash_chain(unsigned char hash_chain[HASH_CHAIN_LENGTH][HASH_LENGTH], const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < HASH_CHAIN_LENGTH; i++) {
        for (int j = 0; j < HASH_LENGTH; j++) {
            fprintf(file, "%02x", hash_chain[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main() {
    unsigned char master_key[HASH_LENGTH];
    unsigned char hash_chain[HASH_CHAIN_LENGTH][HASH_LENGTH];

    read_master_key(master_key, MASTER_KEY_FILE);

    generate_hash_chain(hash_chain, master_key);

    output_hash_chain(hash_chain, OUTPUT_FILE);

    printf("Hash chain generated and saved to %s\n", OUTPUT_FILE);
    return 0;
}