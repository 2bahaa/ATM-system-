/*
 * user.h
 *
 *  Created on: Nov 9, 2024
 *      Author: Administrator
 */

#ifndef USER_H
#define USER_H

typedef struct User {
    int user_id;
    char username[50];
    char password[50];  // Plaintext password in CSV
    float current_balance;
    struct User* next;
} User;

// Function prototypes
User* load_users(const char* filename);
User* authenticate(User* head, int user_id, const char* password);
void save_users(const char* filename, User* head);

#endif // USER_H


