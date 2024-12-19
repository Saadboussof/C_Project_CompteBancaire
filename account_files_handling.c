#include "account.h"

void saveAccountToFile(Account *account)
{
    FILE *file = fopen("accounts.dat", "ab");
    if (file == NULL)
    {
        perror(RED "ERROR : Failed to open accounts file for saving" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
        return;
    }

    if (fwrite(account, sizeof(Account), 1, file) != 1)
    {
        perror(RED "ERROR : Failed to write to accounts file" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
    }
    else
    {
        printf(GREEN "Account saved successfully!\n" RESET);
    }

    fclose(file);
}

void deleteAccountFromFile(long long accountID)
{
    FILE *file = fopen("accounts.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (file == NULL || tempFile == NULL)
    {
        printf(RED "ERROR : Failed to open files for deletion.\n" RESET);
        printf(RED "Failed to delete the request due to a technical issue. Please try again later.\n" RESET);
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
            found = 1;

            // // Check account balance
            // if (account.balance != 0)
            // {
            //     printf(RED "The account cannot be deleted because its balance is %.2f DH.\n" RESET, account.balance);
            //     printf("Please ensure the balance is cleared to proceed with the deletion.\n");

            //     fwrite(&account, sizeof(Account), 1, tempFile); // Keep the account in the file
            //     continue;
            // }

            // // Notify employee of deletion
            // // notifyEmployeeOfDeletion(&account);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("accounts.dat");
        rename("temp.dat", "accounts.dat");
        printf(GREEN "Account deleted successfully.\n" RESET);
    }
    else
    {
        remove("temp.dat");
        printf(RED "Account not found.\n" RESET);
    }
}

void updateAccount(Account *updatedAccount)
{
    // Step 1: Delete the existing account record
    deleteAccountFromFile(updatedAccount->accountID);

    // Step 2: Save the updated account record
    saveAccountToFile(updatedAccount);
}

Account *searchAccountsByClientID(long long ownerID, int *resultCount)
{
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL)
    {
        printf("ERROR : Failed to open file");
        *resultCount = -1;
        exit(EXIT_FAILURE);
    }

    Account *results = NULL;
    Account account;
    size_t count = 0;
    size_t capacity = 10;

    results = (Account *)malloc(capacity * sizeof(Account));
    if (results == NULL)
    {
        printf("ERROR : Failed to allocate memory for results");
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
                    printf("ERROR : Failed to reallocate memory");
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

Account *searchAccountByID(long long accountID) {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("ERROR: Failed to open accounts file.\n");
        exit(EXIT_FAILURE);
    }

    Account *result = (Account *)malloc(sizeof(Account));
    if (result == NULL) {
        printf("ERROR: Failed to allocate memory for the account.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    Account account;
    bool found = false;

    // Read through the file to find the account with the given ID
    while (fread(&account, sizeof(Account), 1, file) == 1) {
        if (account.accountID == accountID) {
            *result = account; // Copy the matching account into result
            found = true;
            break;
        }
    }

    fclose(file);

    if (!found) {
        free(result); // Free the memory if no account was found
        return NULL;
    }

    return result; // Return the found account
}

void saveBankCardToFile(BankCard *bankcard) {
    FILE *file = fopen("bank_card.dat", "ab");
    if (file == NULL) {
        perror(RED "ERROR : Failed to open bank card file for saving" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
        return;
    }

    if (fwrite(bankcard, sizeof(BankCard), 1, file) != 1) {
        perror(RED "ERROR : Failed to write to bank card file" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
    } else {
        printf(GREEN "Bank card saved successfully!\n" RESET);
    }

    fclose(file);
}

BankCard searchBankCardByaccountID(long long accountID)
{
    FILE *file = fopen("bank_card.dat", "rb");

    if (file == NULL)
    {
        printf("ERROR : Failed to open card file");
        exit(EXIT_FAILURE);
    }

    BankCard bankcard;
    while (fread(&bankcard, sizeof(BankCard), 1, file) == 1)
    {
        if (bankcard.cardaccountID == accountID)
        {
            fclose(file);
            return bankcard;
        }
    }
    fclose(file);
    BankCard emptyCard = {0}; // Return an empty BankCard object
    return emptyCard;
}

void deleteBankCardFromFile(long long cardAccountID) {
    FILE *file = fopen("bank_card.dat", "rb");
    if (file == NULL) {
        perror(RED "ERROR : Failed to open bank card file for reading" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
        return;
    }

    FILE *tempFile = fopen("temp_bank_card.dat", "wb");
    if (tempFile == NULL) {
        perror(RED "ERROR : Failed to create temporary file" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
        fclose(file);
        return;
    }

    BankCard bankcard;
    int cardDeleted = 0;

    // Read each record and copy to temp file except the one to delete
    while (fread(&bankcard, sizeof(BankCard), 1, file) == 1) {
        if (bankcard.cardaccountID != cardAccountID) {
            fwrite(&bankcard, sizeof(BankCard), 1, tempFile);
        } else {
            cardDeleted = 1; // Mark that the card to delete was found
        }
    }

    fclose(file);
    fclose(tempFile);

    if (cardDeleted) {
        // Replace original file with temp file
        if (remove("bank_card.dat") != 0 || rename("temp_bank_card.dat", "bank_card.dat") != 0) {
            perror(RED "ERROR : Failed to finalize the card deletion process" RESET);
        } else {
            printf(GREEN "Bank card deleted successfully!\n" RESET);
        }
    } else {
        // No matching card found; remove temp file
        remove("temp_bank_card.dat");
        printf(YELLOW "No bank card found with the given account ID.\n" RESET);
    }
}

void updateBankCard(BankCard *updatedCard) {
    // Delete the old card record based on cardaccountID
    deleteBankCardFromFile(updatedCard->cardaccountID);

    // Save the updated card record
    saveBankCardToFile(updatedCard);

    printf(GREEN "Bank card updated successfully!\n" RESET);
}

void searchByAccountID(long long searchID) {
    FILE *file = fopen("hestorical.bin", "rb"); // Open the historical file
    if (file == NULL) {
        perror("\033[1;31mError opening historical file\033[0m");
        return;
    }

    hestoric record;
    int found = 0;

    // Table Header
    printf("\n\033[1;36m================ Historical Records for Account: %lld =======================\033[0m\n", searchID);
    printf(YELLOW "+---------------+--------------------------------+---------------------------+\n" RESET);
    printf(YELLOW "|" RESET PURPLE "   Amount DH   " RESET YELLOW "|" RESET PURPLE "           Detail               "RESET YELLOW "|" RESET PURPLE "           Date            " RESET YELLOW "|" RESET"\n");
    printf(YELLOW "+---------------+--------------------------------+---------------------------+\n" RESET);

    // Read and display each record for the given account ID
    while (fread(&record, sizeof(hestoric), 1, file) == 1) {
        if (record.AccountID == searchID) {
            // Determine the color for the amount
            const char *amountColor = record.amount < 0 ? "\033[1;31m" : "\033[1;32m"; // Red for < 0, Green otherwise
            printf(YELLOW"|" RESET " %s%10.2f DH " YELLOW "|" RESET " %-30s " YELLOW "|" RESET " %-25s " YELLOW "|\n" RESET, 
                   amountColor, record.amount, record.detail, record.dateop);
            found = 1;
        }
    }

    if (found) {
    // Table Footer
    printf(YELLOW "+---------------+--------------------------------+---------------------------+\n" RESET);
    }

    if (!found) {
        printf(YELLOW "|                                                                            |\n" RESET);
        printf(RED "\n|                No historical records found for this account                |\n"RESET);
        printf(YELLOW "|                                                                            |\n" RESET);
        printf(YELLOW "+---------------+--------------------------------+---------------------------+\n" RESET);
    }

    fclose(file); // Close the file
}

void savehesto(hestoric data)
{
    FILE *file = fopen("hestorical.bin", "ab+"); // "ab" = append in binary mode
    if (file == NULL)
    {
        perror("Error opening file");
    }

    // Write the struct to the file
    fwrite(&data, sizeof(hestoric), 1, file);

    // Close the file
    fclose(file);
    // printf("Data saved successfully.\n");
}
