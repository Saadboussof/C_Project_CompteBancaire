#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "client.h"
#include "tools.h"
#include "file_operations.h"

#define guessing_limit 3

void logIn_Account(long long ownerID)
{
    int resultCount = 0;

    searchAccountsByClientID(ownerID, &resultCount);

    Account *account = (Account *)malloc(resultCount * sizeof(Account));

    account = searchAccountsByClientID(ownerID, &resultCount);

    if ((resultCount == 0) || (account == NULL))
        createAccount();

    char *ACCOUNT_RELATED_TO_OWNERID[resultCount];

    for (int i = 0; i < resultCount; i++)
    {
        ACCOUNT_RELATED_TO_OWNERID[i] = (char *)malloc(50 * sizeof(char));
        strcpy(ACCOUNT_RELATED_TO_OWNERID[i], "Account 01");
    }
    ACCOUNT_RELATED_TO_OWNERID[resultCount + 1] = NULL;

    int index_account = choose_item(ACCOUNT_RELATED_TO_OWNERID, "Your Accounts ");
    Account account_choosen = account[index_account];

    int failed_attempt = 0;
    char PIN[5];

    while (failed_attempt < guessing_limit)
    {
        printf("Enter the PIN of your account: ");
        scanf(" %4s", PIN);

        if (!strcmp(PIN, account_choosen.PIN))
        {
            printf("Account ID: %lld\nOwner ID: %lld\nBalance: %.2f\nType of account: %s\n", account_choosen.accountID, account_choosen.ownerID, account_choosen.balance, account_choosen.accountType);
            printf("kmel l'application\n");
            // les fonctions de lapplication
            break;
        }
        else
        {
            failed_attempt++;
            printf("Incorrect password. Please try again.\n");
        }
    }
    if (failed_attempt == 3)
    {
        account_choosen.isBlocked = 1; // if account is blocked we should check it before open it
        printf("Your account is blocked\n");
    }
}

char *ACCOUN_TYPES[] = {
    "Savings Account",
    "Checking Account",
    "Business Account",
    "Joint Account",
    "Student Account",
    NULL};

void createAccount()
{
    Account newAccount;
    Client *client;

    printf("Creating new account...\n");

    char CIN[9];
    while (1)
    {
        printf("Enter your CIN: ");
        scanf(" %8[^\n]s", CIN);

        // Find the client using CIN
        client = findClientByCIN(CIN);

        if (client == NULL)
        {
            printf("Client not found. May your CIN isn't correct. Try again\n");
        }
        else
            break;
    }

    char password[10];
    while (1)
    {
        printf("Enter your password: ");
        scanf(" %9[^\n]s", password);

        if (strcmp(client->password, password) == 0)
        {
            printf("Correct password!\n");
            break;
        }
        else
        {
            printf("Incorrect password. Please try again.\n");
        }
    }
    newAccount.ownerID = client->clientID;

    printf("Enter initial balance: DH ");
    scanf("%f", &newAccount.balance);

    // int ch;
    // while ((ch = getchar()) != '\n' && ch != EOF)
    //     ; // To clean the BUFFER

    int account_type_index = choose_item(ACCOUN_TYPES, "Types of account");
    strcpy(newAccount.accountType, ACCOUN_TYPES[account_type_index]);

    newAccount.isBlocked = 0;

    printf("Set a PIN with 4 digits: ");
    scanf("%4s", newAccount.PIN);

    newAccount.accountID = generateRandomAccountNumber();
    printf("Your account ID: %lld\n", newAccount.accountID);

    getCurrentDate(newAccount.dateCreated, sizeof(newAccount.dateCreated));
    printf("Account Created on: %s\n", newAccount.dateCreated);

    saveAccountToFile(&newAccount);

    logIn_Account(newAccount.ownerID);
}
