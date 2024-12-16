#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "tools.h"

#define GUESSING_LIMIT 3        // nbr of wrong answers before blocking the account
#define expdate 8               // when the card will expire 
typedef struct
{
    long long cardaccountID;
    char cardNumber[17];       // Numéro de la carte (16 chiffres + '\0')
    char cardHolderName[50];
    char expiryDate[6];        // format MM/YY
    char cvv[4];               // 3 chiffres
    char cardtype[17];        // Type de carte (Visa, Mastercard, etc.)
    float cardbalance;
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

    float *transactionHistory;  // Pointer for transaction history (optional)
    int transactionCount;       // Number of transactions stored

} Account;

// the news by saad
typedef struct 
{
    long long AccountID ;
    float amount ;
    char detail[50];
    char dateop[23];
} hestoric ;

Account *searchAccountsByClientID(long long ownerID, int *resultCount);
Account *searchAccountByID(long long accountID);
void logIn_Account(long long ownerID);
int authenticate_account(Account *selectedAccount);
void creatingAccountRequest(long long ownerID);
void displayAccountDetails(Account account);
void handleAccountBlocking(Account *account);
void requestBankCard(Account account);
void displayBankCardInfo(Account account);
void saveBankCardToFile(BankCard *bankcard);
void deleteBankCardFromFile(long long cardAccountID);
void updateBankCard(BankCard *updatedCard);
BankCard searchBankCardByaccountID(long long accountID);
void saveAccountToFile(Account *account);
void deleteAccountFromFile(long long accountID);
void updateAccount(Account *updatedAccount);
void displayAllAccounts();
int rechargeOnline(Account *account);
int payOnline(Account *account, float amount);
void savehesto(hestoric data);
void searchByAccountID(long long searchID);
void formatString(char *input);

#endif // ACCOUNT_H
