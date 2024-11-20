ATM System Project Description
The ATM System project is a robust simulation of an Automated Teller Machine (ATM) designed to replicate essential banking functionalities in a secure and user-friendly manner. This project emphasizes modularity, secure data handling, and accurate transaction processing. Implemented in the C programming language, the system demonstrates the use of encryption, file handling, and structured programming.

Key Features:
User Authentication:

Secure login using a user ID and password stored in a CSV file.
Passwords are processed with the Hill Cipher encryption algorithm to ensure secure handling during authentication.
Banking Operations:

Balance Inquiry: Users can check their current account balance.
Deposit Funds: Users can add money to their account.
Withdraw Funds: Users can withdraw funds, provided they have sufficient balance.
Transaction History: A complete history of deposits and withdrawals is displayed, with unique transaction IDs for each operation.
Data Storage:

User Data: Stored in users.csv with details such as user ID, username, plaintext passwords, and account balance.
Transaction Data: Stored in transactions.csv, logging each user's transaction type, amount, and unique transaction ID.
Security and Reliability:

Passwords are securely encrypted and handled in memory using the Hill Cipher.
Robust error handling ensures that the system responds gracefully to file access issues or invalid user inputs.
Modularity and Scalability:

The program is divided into multiple files (main.c, user.c, transaction.c, and util.c) for maintainability and future scalability.
Unique transaction ID generation prevents duplication and ensures accurate history tracking.
This project is a comprehensive demonstration of key programming concepts, including encryption, file I/O, data validation, and modular design. It can serve as a foundation for more advanced banking systems or as a learning tool for secure programming practices.
