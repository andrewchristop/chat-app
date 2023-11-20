#include "../include/crypto.h"

void processBlocks(const char *msg, size_t blockSize){
  size_t length = strlen(msg);
  AES_KEY aeskey;
  AES_set_encrypt_key(key, 128, &aeskey);

  for (size_t i = 0; i < length; i += blockSize){
    unsigned char ciphertext[16];
    size_t remainingLength = length - i;
    size_t currentBlockSize;
    
    if (remainingLength < blockSize){
      currentBlockSize = remainingLength;
    }else{
      currentBlockSize = blockSize;
    }

    char block[blockSize + 1];

    strncpy(block, msg + i, currentBlockSize); 

    for (size_t j = currentBlockSize; j < blockSize; ++j){
      block[j] = '\0';
    }

    block[blockSize] = '\0';
    AES_encrypt(block, ciphertext, key);
  }

}
