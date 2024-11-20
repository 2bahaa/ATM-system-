/*
 * transaction.h
 *
 *  Created on: Nov 9, 2024
 *      Author: Administrator
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct Transaction {
    int transaction_id;
    char transaction_type[10];
    float amount;
    int user_id;
    struct Transaction* next;
} Transaction;

// Function declarations
Transaction* load_transactions(const char* filename);
void add_transaction(Transaction** head, int user_id, const char* type, float amount);
void save_transactions(const char* filename, Transaction* head);
void print_transaction_history(Transaction* head, int user_id);

#endif // TRANSACTION_H
