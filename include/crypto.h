#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#define MAX_PLAINTEXT_SIZE 1024

size_t encryptMessage(const unsigned char*, const unsigned char*, size_t, unsigned char [1024]); 
void decryptMessage(const unsigned char*, const unsigned char*, size_t, size_t, size_t, unsigned char []);

