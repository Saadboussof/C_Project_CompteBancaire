#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "client.h"
#include "tools.h"
#include "file_operations.h"

#define GUESSING_LIMIT 3

void logIn_Account(long long ownerID);
void createAccount();
void displayAccountDetails(const Account *account);
void handleAccountBlocking(Account *account);
Account *searchAccountsByClientID(long long ownerID, int *resultCount);
void saveAccountToFile(Account *account);

// allowes the client to select an account by client ID and display its details after verifying their PIN, checking if the account is blocked, and providing the option to create a new account if none exist or want to.
void logIn_Account(long long ownerID)
{
    int resultCount = 0;

    Account *accounts = searchAccountsByClientID(ownerID, &resultCount);
    if (resultCount == 0)
    {
        printf("No accounts found. Creating a new account.\n");
        createAccount();
        return;
    }

    char **accountOptions = malloc((resultCount + 2) * sizeof(char *));
    if (!accountOptions)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < resultCount; i++)
    {
        accountOptions[i] = malloc(50 * sizeof(char));
        if (accountOptions[i] != NULL)
        {
            snprintf(accountOptions[i], 50, "Account %d", i + 1);
        }
    }
    accountOptions[resultCount] = "Create new account"; // The last choice
    accountOptions[resultCount + 1] = NULL;

    int accountSelected = 0;

    while (accountSelected == 0)
    {
        int index_account = choose_item(accountOptions, "Your Accounts ");

        if (index_account == resultCount)
        {
            createAccount();
            return;
        }

        Account selectedAccount = accounts[index_account];

        if (selectedAccount.isBlocked)
        {
            printf("This account is blocked. You cannot log in.\n");
            printf("To unblock your account, please visit our bank during working hours: 9:00 AM to 5:00 PM.\n");
            printf("Please select another account.\n");
            continue; // Skip the rest of the loop and ask the user to choose another account
        }

        char PIN[5];
        int failed_attempts = 0;

        while (failed_attempts < GUESSING_LIMIT)
        {
            printf("Enter the PIN of your account: ");
            PIN_hide(PIN, 5);
            if (validatePIN(PIN, selectedAccount.PIN))
            {
                displayAccountDetails(&selectedAccount);
                accountSelected = 1; // Mark account as successfully selected
                break;
            }
            else
            {
                failed_attempts++;
                printf("Incorrect PIN. Please try again.\n");
            }
        }

        if (failed_attempts == GUESSING_LIMIT)
        {
            handleAccountBlocking(&selectedAccount);
        }
    }

    for (int i = 0; i < resultCount; i++)
    {
        free(accountOptions[i]);
    }
    free(accountOptions);
}

void displayAccountDetails(const Account *account)
{
    if (account == NULL)
    {
        printf("No account details to display.\n");
        return;
    }

    printf("----------- Account Details -----------\n");
    printf("Account ID     : %lld\n", account->accountID);
    printf("Owner ID       : %lld\n", account->ownerID);
    printf("Balance        : %.2f DH\n", account->balance);
    printf("Account Type   : %s\n", account->accountType);
    printf("Account Status : %s\n", account->isBlocked ? "Blocked" : "Active");
    printf("Date Created   : %s\n", account->dateCreated);
    printf("---------------------------------------\n");
}

void handleAccountBlocking(Account *account)
{
    account->isBlocked = 1; // Mark the account as blocked
    printf("Your account has been blocked due to too many incorrect attempts.\n");
    deleteAccountFromFile(account->accountID);
    saveAccountToFile(account);
}

char *ACCOUNT_TYPES[] = {
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
    char CIN[9];
    char PIN[5];

    printf("Creating a new account...\n");

    // Client CIN verification
    while (1)
    {
        printf("Enter your CIN: ");
        scanf(" %8[^\n]s", CIN);

        client = findClientByCIN(CIN);
        if (client == NULL)
        {
            printf("Client not found. Please check your CIN and try again.\n");
        }
        else
        {
            break;
        }
    }

    // Client PIN verification
    while (1)
    {
        printf("Enter your PIN: ");
        PIN_hide(PIN, sizeof(PIN));

        if (validatePIN(client->PIN, PIN))
        {
            printf("PIN verified!\n");
            break;
        }
        else
        {
            printf("Incorrect PIN. Please try again.\n");
        }
    }

    newAccount.ownerID = client->clientID;

    printf("Enter initial balance (in DH): ");
    scanf("%f", &newAccount.balance);

    // Select account type
    int account_type_index = choose_item(ACCOUNT_TYPES, "Types of account");
    strcpy(newAccount.accountType, ACCOUNT_TYPES[account_type_index]);
    newAccount.isBlocked = 0;

    printf("Set a 4-digit PIN: ");
    PIN_hide(newAccount.PIN, sizeof(newAccount.PIN));

    // Generate a random account ID and set creation date
    newAccount.accountID = generateRandomAccountNumber();
    printf("Your account ID: %lld\n", newAccount.accountID);

    getCurrentDate(newAccount.dateCreated, sizeof(newAccount.dateCreated));
    printf("Account created on: %s\n", newAccount.dateCreated);

    saveAccountToFile(&newAccount);
    displayAccountDetails(&newAccount);
    printf("Redirecting to login...\n");
    logIn_Account(newAccount.ownerID);
}

Account *searchAccountsByClientID(long long ownerID, int *resultCount)
{
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        *resultCount = -1;
        exit(EXIT_FAILURE);
    }

    Account *results = NULL;
    Account account;
    size_t count = 0;
    size_t capacity = 10;

    results = malloc(capacity * sizeof(Account));
    if (results == NULL)
    {
        perror("Error allocating memory for results");
        fclose(file);
        *resultCount = -1;
        exit(EXIT_FAILURE);
    }

    while (fread(&account, sizeof(Account), 1, file) == 1)
    {
        if (account.ownerID == ownerID)
        {
            // Increase the capacity of the results array if needed
            if (count >= capacity)
            {
                capacity *= 2; // Double the capacity (so we can avoid multiple reallocations)
                Account *temp = realloc(results, capacity * sizeof(Account));
                if (temp == NULL)
                {
                    perror("Error reallocating memory");
                    free(results);
                    fclose(file);
                    *resultCount = -1;
                    exit(EXIT_FAILURE);
                }
                results = temp;
            }

            results[count++] = account; // Store matching account and then increment count
        }
    }

    fclose(file);

    *resultCount = count; // Set the number of results found
    return results;       // Return the array of results
}

void saveAccountToFile(Account *account)
{
    FILE *file = fopen("accounts.dat", "ab");
    if (file == NULL)
    {
        printf("Failed to open file for saving account.\n");
    }

    fwrite(account, sizeof(Account), 1, file);
    fclose(file);
    printf("Account saved successfully!\n");
}

void deleteAccountFromFile(long long accountID)
{
    FILE *file = fopen("accounts.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (file == NULL || tempFile == NULL)
    {
        printf("Error opening files for deletion.\n");
        if (file)
            fclose(file);
        if (tempFile)
            fclose(tempFile);
        return;
    }

    Account account;
    int found = 0;

    while (fread(&account, sizeof(Account), 1, file) == 1)
    {
        if (account.accountID != accountID)
        {
            fwrite(&account, sizeof(Account), 1, tempFile);
        }
        else
        {
            found = 1; // Without break so we'll make sure all accounts are copied
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("accounts.dat");
        rename("temp.dat", "accounts.dat");
        printf("Account deleted successfully.\n");
    }
    else
    {
        remove("temp.dat");
        printf("Account not found.\n");
    }
}
