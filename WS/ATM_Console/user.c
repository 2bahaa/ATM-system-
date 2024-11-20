#include "user.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to load users from a CSV file into a linked list
User* load_users(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening users file\n");
        return NULL;
    }

    User* head = NULL;
    User* tail = NULL;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        User* new_user = (User*)malloc(sizeof(User));
        sscanf(buffer, "%d,%49[^,],%49[^,],%f", &new_user->user_id, new_user->username, new_user->password, &new_user->current_balance);
        new_user->next = NULL;

        if (!head) {
            head = new_user;
        } else {
            tail->next = new_user;
        }
        tail = new_user;
    }

    fclose(file);
    return head;
}

// Function to authenticate a user using user ID and password
User* authenticate(User* head, int user_id, const char* password) {
    User* current = head;
    char encrypted_input_password[50];  // Encrypted password entered by the user
    char encrypted_stored_password[50]; // Encrypted password from the CSV file

    // Encrypt the entered password using Hill Cipher
    encrypt(password, encrypted_input_password);

    while (current) {
        // Encrypt the stored password from the CSV file using Hill Cipher
        encrypt(current->password, encrypted_stored_password);

        // Compare the encrypted input password with the encrypted password from the file
        if (current->user_id == user_id && strcmp(encrypted_input_password, encrypted_stored_password) == 0) {
            return current;  // Return the user if authentication succeeds
        }
        current = current->next;
    }
    return NULL;  // Return NULL if authentication fails
}

// Function to save users to a CSV file with encrypted passwords
// Function to save users to a CSV file with encrypted passwords
void save_users(const char* filename, User* head) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening users file for writing. Make sure the directory is writable.\n");
        return;
    }

    User* current = head;
    while (current) {
        fprintf(file, "%d,%s,%s,%.2f\n", current->user_id, current->username, current->password, current->current_balance);
        current = current->next;
    }

    fclose(file);
    printf("Users saved successfully.\n");
}

