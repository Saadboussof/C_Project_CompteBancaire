#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "account.h"

int saveClientToFile(Client *client);

void saveAccountToFile(Account *account);

Account* searchAccountsByClientID(long long ownerID, int *resultCount);

void loadAccountsFromFile();

void deleteAccountFromFile(long long accountNumber);
Client *findClientByCIN(const char *CIN);

#endif // FILE_OPERATIONS_H
