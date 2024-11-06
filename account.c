#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "client.h"
#include "tools.h"
#include "file_operations.h"

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

    printf("Creating new account...\n");

    char CIN[9];
    printf("Enter your CIN: ");
    scanf(" %8[^\n]s", CIN);

    // Find the client using CIN
    Client *client = findClientByCIN(CIN);
    if (client == NULL)
    {
        printf("Client not found. Please register first.\n");
        createClient();
        return;
    }

    newAccount.ownerID = client->clientID;

    newAccount.accountID = generateRandomAccountNumber();
    printf("Your account ID: %lld\n", newAccount.accountID);

    printf("Enter initial balance: DH ");
    scanf("%f", &newAccount.balance);

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ; // To clean the BUFFER

    int account_type_index = choose_item(ACCOUN_TYPES, "Types of account");
    strcpy(newAccount.accountType, ACCOUN_TYPES[account_type_index]);

    getCurrentDate(newAccount.dateCreated, sizeof(newAccount.dateCreated));
    printf("Account Created on: %s\n", newAccount.dateCreated);

    saveAccountToFile(&newAccount);
}
