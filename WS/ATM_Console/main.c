/*
 * main.c
 *
 *  Created on: Nov 9, 2024
 *      Author: Administrator
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "transaction.h"
#include "util.h"

// Function to display the ATM menu
void display_menu() {
    printf("ATM Menu:\n");
    printf("1. Balance Inquiry\n");
    printf("2. Deposit Funds\n");
    printf("3. Withdraw Funds\n");
    printf("4. Transaction History\n");
    printf("5. Exit\n");
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    // Load users and transactions from CSV files
    User* users = load_users("users.csv");
    Transaction* transactions = load_transactions("transactions.csv");

    if (!users || !transactions) {
        printf("Failed to load data.\n");
        return 1;
    }

    User* user = NULL;
    int user_id;
    char password[50];

    // Authentication loop
    while (user == NULL) {
        printf("Enter user ID: ");
        scanf("%d", &user_id);
        printf("Enter password: ");
        scanf("%49s", password);

        // Authenticate user
        user = authenticate(users, user_id, password);
        if (!user) {
            printf("Authentication failed. Please try again.\n");
        }
    }

    int choice;
    do {
        display_menu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // Balance Inquiry
            printf("Current balance: %.2f\n", user->current_balance);
            break;
        case 2: {
            // Deposit Funds
            float amount;
            printf("Enter deposit amount: ");
            scanf("%f", &amount);
            user->current_balance += amount;
            add_transaction(&transactions, user->user_id, "deposit", amount);
            printf("Deposit successful. New balance: %.2f\n", user->current_balance);
            break;
        }
        case 3: {
            // Withdraw Funds
            float amount;
            printf("Enter withdrawal amount: ");
            scanf("%f", &amount);
            if (amount > user->current_balance) {
                printf("Insufficient funds.\n");
            } else {
                user->current_balance -= amount;
                add_transaction(&transactions, user->user_id, "withdraw", amount);
                printf("Withdrawal successful. New balance: %.2f\n", user->current_balance);
            }
            break;
        }
        case 4:
            // Transaction History
            printf("Transaction history:\n");
            print_transaction_history(transactions, user->user_id);
            break;
        case 5:
            // Exit
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    // Save updated users and transactions back to CSV files
    save_users("users.csv", users);
    save_transactions("transactions.csv", transactions);

    return 0;
}
