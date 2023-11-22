#include "../include/crypto.h"


void processBlocks(char *msg, size_t blockSize, char cipher[1024]){
  unsigned char key[16] = "mysecretkey1234";
  AES_KEY aeskey;
  AES_set_encrypt_key((const unsigned char *)key, 128, &aeskey);
  unsigned char iv[AES_BLOCK_SIZE];
  RAND_bytes(iv, AES_BLOCK_SIZE);
  AES_cbc_encrypt((const unsigned char *)msg, (unsigned char* )cipher, strlen(msg), &aeskey, iv, AES_ENCRYPT);
}
