#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "client.h"
typedef struct
{
  long long accountID;
  float balance;
  char accountType[20];
  char dateCreated[23];
  long long ownerID;
  char password[50];
  // int isBlocked;

  // float *transactionHistory;  // Pointer for transaction history (optional)
  // int transactionCount;       // Number of transactions stored

} Account;

char *ACCOUNT_TYPES[] = {
    "Savings Account",
    "Checking Account",
    "Business Account",
    "Joint Account",
    "Student Account"
};

void createAccount();
// void deleteAccount();
// void displayAccount();

#endif // ACCOUNT_H
