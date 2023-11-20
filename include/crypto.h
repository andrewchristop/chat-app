#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void processBlocks(const char *, size_t);
void decryptMessage(const unsigned char *, const unsigned char *);
void encryptMessage(const unsigned char *, const unsigned char *);

