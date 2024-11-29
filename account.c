#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "account.h"
#include "client.h"
#include "tools.h"

#define GUESSING_LIMIT 3
#define CYAN "\033[0;36m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define RED "\033[31m"
#define ORANGE "\033[38;5;214m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void logIn_Account(long long ownerID);
void creatingAccountRequest(long long ownerID);
void displayAccountDetails(const Account *account);
void handleAccountBlocking(Account *account);
void requestBankCard(Account *account);
void saveRequestaccountToFile(const Account *newRequest);
Account *searchAccountsByClientID(long long ownerID, int *resultCount);
void saveAccountToFile(Account *account);
void displayAllAccounts();
void deleteAccountFromFile(long long accountID);

// Select client's account and Log in by PIN if not blocked and New account creation

void logIn_Account(long long ownerID)
{
    int resultCount = 0;

    Account *accounts = searchAccountsByClientID(ownerID, &resultCount);
    if (resultCount == 0)
    {
        printf(BLUE "No accounts found. Creating a new account...\n" RESET);
        creatingAccountRequest(ownerID);
        return;
    }

    char **accountOptions = malloc((resultCount + 2) * sizeof(char *));
    if (!accountOptions)
    {
        fprintf(stderr, RED "Memory allocation failed.\n" RESET);
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
            creatingAccountRequest(ownerID);
            return;
        }

        Account selectedAccount = accounts[index_account];

        if (selectedAccount.isBlocked)
        {
            printf(RED "This account is blocked. You cannot log in.\n" RESET);
            printf(BLUE "To unblock your account, please visit our bank during working hours: 9:00 AM to 5:00 PM.\n" RESET);
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
        printf(ORANGE "No account details to display.\n" RESET);
        return;
    }

    printf(PURPLE "----------- Account Details -----------\n" RESET);
    printf("Account ID     : %lld\n", account->accountID);
    printf("Owner ID       : %lld\n", account->ownerID);
    printf("Balance        : %.2f DH\n", account->balance);
    printf("Account Type   : %s\n", account->accountType);
    printf("Account Status : %s\n", account->isBlocked ? RED "Blocked" RESET : GREEN "Active" RESET);
    printf("Date Created   : %s\n", account->dateCreated);
    printf(PURPLE "---------------------------------------\n" RESET);
}

void handleAccountBlocking(Account *account)
{
    account->isBlocked = 1; // Mark the account as blocked
    printf(RED "Your account has been blocked due to too many incorrect attempts.\n" RESET);
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

char *CARD_TYPES[] = {
    "Visa",
    "Mastercard",
    "American Express",
    "Discover",
    NULL};

void creatingAccountRequest(long long ownerID)
{
    Account newAccount;
    
    newAccount.ownerID = ownerID;

    // The balance of a new Account is 0.00 and it's unblocked.
    newAccount.balance = 0.00;
    
    newAccount.isBlocked = 0;

    // Select account type:
    int account_type_index = choose_item(ACCOUNT_TYPES, "Types of account");
    strcpy(newAccount.accountType, ACCOUNT_TYPES[account_type_index]);

    // PIN setting: 
    int check;
    char PIN[5];
    while (1)
    {
        while (!check)
        {
            printf("Set a 4-digit PIN: ");
            PIN_hide(newAccount.PIN, sizeof(newAccount.PIN));
            check = ((strlen(newAccount.PIN) == 4) && isNumericString(newAccount.PIN));
        }
        check = 0;
        
        printf("Confirme your PIN: ");
        PIN_hide(PIN, sizeof(PIN));
        
        if (!validatePIN(newAccount.PIN, PIN))
            printf(ORANGE "PIN incorrect.\nTry again.\n" RESET);
        
        else
            break;
    }

    // Generate a random account ID and set creation date:
    newAccount.accountID = generateRandomAccountNumber();
    printf("Your account ID: %lld\n", newAccount.accountID);

    getCurrentDate(newAccount.dateCreated, sizeof(newAccount.dateCreated));
    printf("Account created on: %s\n", newAccount.dateCreated);

    // Ask if the client wants a bank card
    requestBankCard(&newAccount);

    // Save the request of account creation in the request file:
    saveRequestaccountToFile(&newAccount);

    printf(GREEN "Your account creation request has been submitted successfully!\n" RESET);
}

void requestBankCard(Account *account) {
    char response[2];
    printf(BLUE "Would you like to request a bank card? (y/n): " RESET);
    scanf("%1s", response);

    // Convert input to lowercase for easier comparison
    response[0] = tolower(response[0]);

    if (strcmp(response, "y") == 0) {
        // Allocate memory for BankCard
        account->bankCard = (BankCard *)malloc(sizeof(BankCard));

        // Display card types for the user to choose
        int cardTypeIndex = choose_item(CARD_TYPES, "Choose a card type");
        strcpy(account->bankCard->typeCarte, CARD_TYPES[cardTypeIndex]);

        // Fetch the cardholder's name based on the owner's ID
        strcpy(account->bankCard->cardHolderName, "utilisateur"/* getClientName(account->ownerID) */);

        // Calculate expiry date (8 years from the current date)
        char currentDate[20];       // Format: YYYY-MM-DD at HH:MM:SS
        getCurrentDate(currentDate, sizeof(currentDate));

        // Extract the year from current date and add 8 years to it
        int currentYear = atoi(currentDate); // Extract year from "YYYY-MM-DD"
        int expiryYear = currentYear + 8;

        // Format expiry date (MM/YY)
        int expiryMonth = atoi(&currentDate[5]); // Extract month from "YYYY-MM-DD"
        snprintf(account->bankCard->expiryDate, sizeof(account->bankCard->expiryDate), "%02d/%02d", expiryMonth, expiryYear % 100);

        // Randomly generate CVV (3 digits)
        snprintf(account->bankCard->cvv, sizeof(account->bankCard->cvv), "%03d", rand() % 1000);

        // Generate the full card number using the account ID and random digits
        snprintf(account->bankCard->cardNumber, sizeof(account->bankCard->cardNumber), "4000%lld%04d", account->accountID, rand() % 10000);


        // Set card as not blocked (default is unblocked)
        account->bankCard->cardBlocked = 0;

        // Prompt for a PIN for the card
        int check;
        char PIN[5];
        while (1)
        {
            while (!check)
            {
                printf("Set a 4-digit PIN for your card: ");
                PIN_hide(account->bankCard->PIN, sizeof(account->bankCard->PIN));
                check = ((strlen(account->bankCard->PIN) == 4) && isNumericString(account->bankCard->PIN));
            }
            check = 0;
            
            printf("Confirme your PIN: ");
            PIN_hide(PIN, sizeof(PIN));
            
            if (!validatePIN(account->bankCard->PIN, PIN))
                printf(ORANGE "PIN incorrect.\nTry again.\n" RESET);
            
            else
                break;
        }

        // Inform the user that the card request is successful
        printf(GREEN "Your card request has been successfully submitted. You can collect it at the bank once approved.\n" RESET);
    } 
    else if (strcmp(response, "n") == 0) {
        printf(ORANGE "You have declined the bank card request.\n" RESET);
    } 
    else {
        printf(RED "Invalid response. Please answer 'y' or 'n'.\n" RESET);
    }
}

void saveRequestaccountToFile(const Account *newRequest) {
    FILE *file = fopen("account_requests.dat", "rb+");
    if (file == NULL) {
        perror(RED "Error opening the request file" RESET);
        printf(RED "Failed to save the request due to a technical issue. Please try again later.\n" RESET);
        exit(EXIT_FAILURE);
    }

    Account existingRequest;
    int found = 0;
    long position = 0;

    // Search for existing request with the same ownerID
    while (fread(&existingRequest, sizeof(Account), 1, file) == 1) {
        if (existingRequest.ownerID == newRequest->ownerID) {
            found = 1;
            break;
        }
        position += sizeof(Account);
    }

    if (found) {
        printf(ORANGE "A request already exists for owner ID %lld.\n" RESET, newRequest->ownerID);
        printf("1 - Keep the old request\n");
        printf("2 - Replace it with the new request\n");

        int choice;
        scanf("%1d", &choice);

        if (choice == 1) {
            printf(GREEN "The new request was canceled, and the old request remains unchanged.\n" RESET);
        } else if (choice == 2) {
            fseek(file, position, SEEK_SET);
            fwrite(newRequest, sizeof(Account), 1, file);
            printf(GREEN "The old request was replaced with the new one successfully.\n" RESET);
        } else {
            printf(YELLOW "Invalid choice. No changes were made.\n" RESET);
        }
    } else {
        // Append new request if no duplicate is found
        fseek(file, 0, SEEK_END);
        fwrite(newRequest, sizeof(Account), 1, file);
        printf(GREEN "Your account request has been saved and is pending approval.\n" RESET);
    }

    fclose(file);
}

Account *searchAccountsByClientID(long long ownerID, int *resultCount) {
    FILE *file = fopen("account_requests.dat", "rb");
    if (file == NULL) {
        perror(RED "Error opening accounts file" RESET);
        printf(RED "An issue occurred while accessing account data. Please try again later or contact support.\n" RESET);
        *resultCount = -1;
        exit(EXIT_FAILURE);
    }

    Account *results = malloc(10 * sizeof(Account));
    if (results == NULL) {
        perror(RED "Memory allocation failed" RESET);
        printf(RED "A critical error occurred. Please try again later.\n" RESET);
        fclose(file);
        *resultCount = -1;
        exit(EXIT_FAILURE);
    }

    Account account;
    size_t count = 0, capacity = 10;

    while (fread(&account, sizeof(Account), 1, file) == 1) {
        if (account.ownerID == ownerID) {
            // Increase the capacity of the results array if needed
            if (count >= capacity) {
                capacity *= 2; // Double the capacity (so we can avoid multiple reallocations)
                Account *temp = realloc(results, capacity * sizeof(Account));
                if (temp == NULL) {
                    perror(RED "Memory reallocation failed" RESET);
                    printf(RED "Failed to process accounts due to a technical issue. Please try again.\n" RESET);
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

    if (count == 0) {
        free(results);
        results = NULL;
    }

    fclose(file);
    *resultCount = count; // Set the number of results found
    return results; // Return the array of results
}


void saveAccountToFile(Account *account) {
    FILE *file = fopen("accounts.dat", "ab");
    if (file == NULL) {
        perror(RED "Error opening accounts file for saving" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
        return;
    }

    if (fwrite(account, sizeof(Account), 1, file) != 1) {
        perror(RED "Error writing to accounts file" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
    } else {
        printf(GREEN "Account saved successfully!\n" RESET);
    }

    fclose(file);
}


// void notifyEmployeeOfDeletion(const Account *account) {
//     // Notify the employee about the account deletion
//     printf(GREEN "Notification sent to employee:\n" RESET);
//     printf(BLUE "Deleted Account Details:\n" RESET);
//     printf("  Account ID: %lld\n", account->accountID);
//     printf("  Owner ID: %lld\n", account->ownerID);
//     printf("  Account Type: %s\n", account->accountType);
//     printf("  Balance Before Deletion: %.2f DH\n", account->balance);
//     printf("  Deletion Date: %s\n", getCurrentDate());
//     printf(GREEN "Please log this activity for records.\n" RESET);
// }

void deleteAccountFromFile(long long accountID) {
    FILE *file = fopen("accounts.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (file == NULL || tempFile == NULL) {
        printf(RED "Error opening files for deletion.\n" RESET);
        printf(RED "Failed to delete the request due to a technical issue. Please try again later.\n" RESET);
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    Account account;
    int found = 0;

    while (fread(&account, sizeof(Account), 1, file) == 1) {
        if (account.accountID != accountID) {
            fwrite(&account, sizeof(Account), 1, tempFile);
        } else {
            found = 1;

            // Check account balance
            if (account.balance != 0) {
                printf(ORANGE "The account cannot be deleted because its balance is %.2f DH.\n" RESET, account.balance);
                printf(PURPLE "Please ensure the balance is cleared to proceed with the deletion.\n" RESET);

                fwrite(&account, sizeof(Account), 1, tempFile); // Keep the account in the file
                continue;
            }

            // Notify employee of deletion
            // notifyEmployeeOfDeletion(&account);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("accounts.dat");
        rename("temp.dat", "accounts.dat");
        printf(GREEN "Account deleted successfully.\n" RESET);
    } else {
        remove("temp.dat");
        printf(RED "Account not found.\n" RESET);
    }
}


void displayAllAccounts()
{
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL)
    {
        printf(RED "Error: Unable to open the accounts file.\n" RESET);
        return;
    }

    Account account;
    int accountCount = 0;

    printf("--------------- All Accounts ---------------\n");
    while (fread(&account, sizeof(Account), 1, file) == 1)
    {
        printf("Account #%d\n", ++accountCount);
        printf("Account ID     : %lld\n", account.accountID);
        printf("Owner ID       : %lld\n", account.ownerID);
        printf("Balance        : %.2f DH\n", account.balance);
        printf("Account Type   : %s\n", account.accountType);
        printf("Account Status : %s\n", account.isBlocked ? "Blocked" : "Active");
        printf("Date Created   : %s\n", account.dateCreated);
        printf("-------------------------------------------\n");
    }

    if (accountCount == 0)
    {
        printf("No accounts found.\n");
    }
    else
    {
        printf("Total Accounts: %d\n", accountCount);
    }

    fclose(file);
}

