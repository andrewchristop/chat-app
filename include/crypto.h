#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

void processBlocks(char *, size_t, char[]);
void decryptMessage(const unsigned char *, const unsigned char *);
void encryptMessage(const unsigned char *, const unsigned char *);

