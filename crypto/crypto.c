#include "../include/crypto.h"


void processBlocks(char *msg, size_t blockSize, char cipher[1024]){
  unsigned char key[16] = "mysecretkey4444";
  size_t length = strlen(msg);
  AES_KEY aeskey;
  AES_set_encrypt_key(key, 128, &aeskey);
  
  for (size_t i = 0; i < length; i += blockSize){
    char ciphertext[16];
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
    AES_encrypt((const unsigned char*)block, (unsigned char *)ciphertext, &aeskey);

    if (i == 0){
      strcpy(cipher, ciphertext);
    }else{
      strcat(cipher, ciphertext);
    }

  }


}
