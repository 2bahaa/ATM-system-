#include "transaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to load transactions from a CSV file into a linked list
Transaction* load_transactions(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening transactions file\n");
        return NULL;
    }

    Transaction* head = NULL;
    Transaction* tail = NULL;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        Transaction* new_transaction = (Transaction*)malloc(sizeof(Transaction));
        sscanf(buffer, "%d,%9[^,],%f,%d", &new_transaction->transaction_id, new_transaction->transaction_type, &new_transaction->amount, &new_transaction->user_id);
        new_transaction->next = NULL;

        if (!head) {
            head = new_transaction;
        } else {
            tail->next = new_transaction;
        }
        tail = new_transaction;
    }

    fclose(file);
    return head;
}

// Function to add a transaction
void add_transaction(Transaction** head, int user_id, const char* type, float amount) {
    // Create a unique transaction ID using user_id and number of transactions
    static int transaction_counter = 1;  // Static counter to ensure unique IDs for each user
    int transaction_id = user_id * 1000 + transaction_counter++;  // Combining user ID with a counter to generate unique IDs

    Transaction* new_transaction = (Transaction*)malloc(sizeof(Transaction));
    new_transaction->transaction_id = transaction_id;  // Assign unique transaction ID
    strcpy(new_transaction->transaction_type, type);
    new_transaction->amount = amount;
    new_transaction->user_id = user_id;
    new_transaction->next = *head;
    *head = new_transaction;
}

// Function to save transactions to a CSV file
void save_transactions(const char* filename, Transaction* head) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening transactions file for writing. Make sure the directory is writable.\n");
        return;
    }

    Transaction* current = head;
    while (current) {
        fprintf(file, "%d,%s,%.2f,%d\n", current->transaction_id, current->transaction_type, current->amount, current->user_id);
        current = current->next;
    }

    fclose(file);
    printf("Transactions saved successfully.\n");
}


// Function to print the transaction history for a user
void print_transaction_history(Transaction* head, int user_id) {
    Transaction* current = head;
    while (current) {
        if (current->user_id == user_id) {
            printf("ID: %d, Type: %s, Amount: %.2f\n", current->transaction_id, current->transaction_type, current->amount);
        }
        current = current->next;
    }
}
