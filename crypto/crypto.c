#include "../include/crypto.h"

size_t encryptMessage(const unsigned char *plaintext, const unsigned char *key, size_t plaintextLen, unsigned char ciphertext [1024]){
  AES_KEY aesKey;
  AES_set_encrypt_key(key, 128, &aesKey);

  size_t paddedLen = ((plaintextLen + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
  unsigned char paddedPlaintext[MAX_PLAINTEXT_SIZE];
  //unsigned char ciphertext[MAX_PLAINTEXT_SIZE];
  memcpy(paddedPlaintext, plaintext, plaintextLen);
  memset(paddedPlaintext + plaintextLen, AES_BLOCK_SIZE - (plaintextLen % AES_BLOCK_SIZE), AES_BLOCK_SIZE - (plaintextLen % AES_BLOCK_SIZE));

  for (size_t i = 0; i < paddedLen; i += AES_BLOCK_SIZE){
    AES_encrypt(paddedPlaintext + i, ciphertext + i, &aesKey);
  }
  return(paddedLen);
}

void decryptMessage(const unsigned char *ciphertext, const unsigned char *key, size_t ciphertextLen, size_t plaintextLen, size_t paddedLen, unsigned char decrypted[]) {
  AES_KEY aesKey;
  AES_set_decrypt_key(key, 128, &aesKey);

  for(size_t i = 0; i < MAX_PLAINTEXT_SIZE; i += AES_BLOCK_SIZE){
    AES_decrypt(ciphertext + i, decrypted + i, &aesKey);
  }
  
}

