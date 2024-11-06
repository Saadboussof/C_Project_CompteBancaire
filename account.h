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
    char PIN[5];
    int isBlocked;

    // float *transactionHistory;  // Pointer for transaction history (optional)
    // int transactionCount;       // Number of transactions stored

} Account;

void logIn_Account(long long ownerID);
void createAccount();
// void deleteAccount();
// void displayAccount();

#endif // ACCOUNT_H
