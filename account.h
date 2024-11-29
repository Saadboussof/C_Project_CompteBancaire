#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "tools.h"

#define GUESSING_LIMIT 3
#define expdate 8
typedef struct
{
    char cardNumber[17];       // Numéro de la carte (16 chiffres + '\0')
    char cardHolderName[50];
    char expiryDate[6];        // format MM/YY
    char cvv[4];               // 3 chiffres
    char typeCarte[10];        // Type de carte (Visa, Mastercard, etc.)
    int cardBlocked;         // 0 for unblocked, 1 for blocked
    char PIN[5];           // 4-digit PIN (with null terminator)
} BankCard;
typedef struct
{
    long long accountID;
    long long ownerID;
    float balance;
    char accountType[20];
    char PIN[5];             // 4-digit PIN (with null terminator)
    int isBlocked;           // 0 for unblocked account
    char dateCreated[23];
    BankCard *bankCard;       // Pointer to BankCard (NULL if no card)

    float *transactionHistory;  // Pointer for transaction history (optional)
    int transactionCount;       // Number of transactions stored

} Account;

Account *searchAccountsByClientID(long long ownerID, int *resultCount);
void logIn_Account(long long ownerID);
int authenticate_account(Account *selectedAccount);
void creatingAccountRequest(long long ownerID);
void displayAccountDetails(Account *account);
void handleAccountBlocking(Account *account);
void requestBankCard(Account *account);
void displayBankCardInfo(BankCard *bankCard);
void saveAccountToFile(Account *account);
void displayAllAccounts();
void deleteAccountFromFile(long long accountID);

#endif // ACCOUNT_H
