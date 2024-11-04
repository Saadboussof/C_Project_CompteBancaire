#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "account.h"

int saveClientToFile(Client *client);

int saveAccountToFile(Account *account);

void loadAccountsFromFile();

void deleteAccountFromFile(long long accountNumber);

#endif // FILE_OPERATIONS_H
