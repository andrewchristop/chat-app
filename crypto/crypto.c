#include "../include/crypto.h"


void processBlocks(char *msg, size_t blockSize, char cipher[1024]){
  char block[16];
  unsigned char temp[1024];
  unsigned char key[16] = "mysecretkey1234";
  size_t sizeIB = strlen(msg);
  AES_KEY aeskey;
  AES_set_encrypt_key(key, 128, &aeskey);
  size_t cipherIndex = 0;

  for (size_t i = 0; i < sizeIB; i += blockSize){
    memset(block, 0, sizeof(block));
    strncpy(block, msg + i, blockSize);
    AES_encrypt((const unsigned char *) block, temp, &aeskey);
    memcpy(cipher + cipherIndex, temp, sizeof(temp));
    cipherIndex += sizeof(temp);
  }
}
