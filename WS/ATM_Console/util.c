/*
 * util.c
 *
 *  Created on: Nov 20, 2024
 *      Author: Mohamed Bahaa
 */


// util.c
// util.c - Hill Cipher
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26  // For Hill Cipher

// Hill Cipher 2x2 matrix key
const int key[2][2] = {{3, 3}, {2, 5}};  // Example key for the Hill Cipher

// Function to encrypt a plaintext string using Hill Cipher
void encrypt(const char* plaintext, char* ciphertext) {
    int len = strlen(plaintext);
    if (len % 2 != 0) {
        len++;  // If the plaintext length is odd, pad with 'X'
    }

    for (int i = 0; i < len; i += 2) {
        int p1 = toupper(plaintext[i]) - 'A';  // Convert to 0-25 range (A=0, B=1, ..., Z=25)
        int p2 = (i + 1 < strlen(plaintext)) ? toupper(plaintext[i + 1]) - 'A' : 'X' - 'A'; // Use 'X' for padding

        ciphertext[i] = ((key[0][0] * p1 + key[0][1] * p2) % MOD) + 'A';  // Encrypt using Hill Cipher
        ciphertext[i + 1] = ((key[1][0] * p1 + key[1][1] * p2) % MOD) + 'A';
    }
    ciphertext[len] = '\0';  // Null-terminate the string
}

// Function to decrypt a ciphertext string using Hill Cipher
void decrypt(const char* ciphertext, char* plaintext) {
    int len = strlen(ciphertext);

    // Determinant of the matrix (mod 26)
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
    if (det < 0) det += MOD;

    // Finding modular inverse of determinant (det * inv_det ≡ 1 mod 26)
    int inv_det = 0;
    for (int i = 1; i < MOD; i++) {
        if ((det * i) % MOD == 1) {
            inv_det = i;
            break;
        }
    }

    // Adjoint matrix
    int adj[2][2] = {{key[1][1], -key[0][1]}, {-key[1][0], key[0][0]}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            adj[i][j] = (adj[i][j] * inv_det) % MOD;  // Applying inverse to adjoint matrix
            if (adj[i][j] < 0) adj[i][j] += MOD;  // Handle negative values
        }
    }

    for (int i = 0; i < len; i += 2) {
        int c1 = toupper(ciphertext[i]) - 'A';  // Convert to 0-25 range
        int c2 = toupper(ciphertext[i + 1]) - 'A';

        plaintext[i] = ((adj[0][0] * c1 + adj[0][1] * c2) % MOD) + 'A';  // Decrypt using the inverse matrix
        plaintext[i + 1] = ((adj[1][0] * c1 + adj[1][1] * c2) % MOD) + 'A';
    }
    plaintext[len] = '\0';  // Null-terminate the string
}
