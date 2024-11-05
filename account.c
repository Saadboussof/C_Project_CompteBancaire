#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "client.h"
#include "tools.h"
#include "file_operations.h"

void createAccount()
{
  Account newAccount;

  printf("Creating a new account...\n");

  printf("Enter your client ID: ");
  scanf("%lld", &newAccount.ownerID);

  newAccount.accountID = generateRandomAccountNumber();
  printf("Your account ID: %lld\n", newAccount.accountID);

  printf("Enter initial balance: ");
  scanf("%f", &newAccount.balance);

  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF)
    ; // To clean the BUFFER

  printf("Choose your account type: ");
  scanf("%s", &newAccount.accountType);
  
  getCurrentDate(newAccount.dateCreated, sizeof(newAccount.dateCreated));
  printf("Account Created on: %s\n", newAccount.dateCreated);

  saveAccountToFile(&newAccount);
}
