#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "client.h"

typedef struct
{
  long long accountID;
  float balance;
  char accountType[20]; // TODO: add the list of choices :("Savings", "Checking", ...)
  char dateCreated[23];
  long long ownerID;
  int isBlocked;

  // float *transactionHistory;  // Pointer for transaction history (optional)
  // int transactionCount;       // Number of transactions stored

} Account;

void createAccount();
// void deleteAccount();
// void displayAccount();

#endif
