#include "account.h"

void displayAccountDetails(Account *account)
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
    // displayBankCardInfo(account->bankCard);
}

void displayBankCardInfo(BankCard *bankCard) {
    if (bankCard == NULL) {
        printf(RED "No bank card information available.\n" RESET);
        return;
    }
    printf("\n" PURPLE "Bank Card Information:\n" RESET);
    printf(PURPLE "=====================================\n" RESET);
    printf(CYAN "Cardholder Name: " RESET "%s\n", bankCard->cardHolderName);

    // Mask all but the last 4 digits of the card number
    printf(CYAN "Card Number:     " RESET "**** **** **** %s\n", bankCard->cardNumber[12]);

    printf(CYAN "Card Type:       " RESET "%s\n", bankCard->typeCarte);
    printf(CYAN "Expiry Date:     " RESET "%s\n", bankCard->expiryDate);

    // Show CVV (for confirmation, mask in production)
    printf(CYAN "CVV:             " RESET "%s\n", bankCard->cvv);

    // Show card status
    printf(CYAN "Card Status:     " RESET "%s\n", bankCard->cardBlocked ? RED "Blocked" RESET : GREEN "Active" RESET);

    printf(PURPLE "=====================================\n" RESET);
}

void displayAllAccounts()
{
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL)
    {
        printf(RED "ERROR: Failed to open the accounts file.\n" RESET);
        return;
    }

    Account account;
    int accountCount = 0;

    printf("------------------------- All Accounts -------------------------\n");
    while (fread(&account, sizeof(Account), 1, file) == 1)
    {
        printf("Account #%d\n", ++accountCount);
        printf("Account ID     : %lld\n", account.accountID);
        printf("Owner ID       : %lld\n", account.ownerID);
        printf("Balance        : %.2f DH\n", account.balance);
        printf("Account Type   : %s\n", account.accountType);
        printf("Account Status : %s\n", account.isBlocked ? RED "Blocked" RESET : GREEN "Active" RESET);
        printf("Date Created   : %s\n", account.dateCreated);
        printf(YELLOW "-------------------------------------------\n" RESET);
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




