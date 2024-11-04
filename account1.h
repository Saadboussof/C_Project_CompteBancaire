#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    int accountNumber;
    double balance;
} Account;

void createAccount(Account *acc, int accountNumber);
void displayAccount();

#endif 