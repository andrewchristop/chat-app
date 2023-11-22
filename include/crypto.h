#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

void processBlocks(const char *, char[]);
void decryptMessage(const char *, char[]);

