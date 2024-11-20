/*
 * util.h
 *
 *  Created on: Nov 20, 2024
 *      Author: Mohamed Bahaa
 */

#ifndef UTIL_H_
#define UTIL_H_

// Hill Cipher encryption key (2x2 matrix) and modular base
#define MOD 26

// Function to encrypt a plaintext string using Hill Cipher
void encrypt(const char* plaintext, char* ciphertext);

// Function to decrypt a ciphertext string using Hill Cipher
void decrypt(const char* ciphertext, char* plaintext);


#endif /* UTIL_H_ */
