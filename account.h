#include "client.h"

#ifndef ACCOUNT_H
#define ACCOUNT_H
typedef struct
{
    long long accountID;
    float balance;
    char accountType[20];
    char dateCreated[23];
    long long ownerID;
    char PIN[5];             // 4-digit PIN (with null terminator)
    int isBlocked;           // 0 for unblocked account

    // float *transactionHistory;  // Pointer for transaction history (optional)
    // int transactionCount;       // Number of transactions stored

} Account;

void logIn_Account(long long ownerID);
void createAccount();
void displayAccountDetails(const Account *account);
void handleAccountBlocking(Account *account);
Account *searchAccountsByClientID(long long ownerID, int *resultCount);
void saveAccountToFile(Account *account);
void deleteAccountFromFile(long long accountNumber);

// void deleteAccount();


#endif // ACCOUNT_H
