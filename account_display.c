#include "account.h"

void displayAccountDetails(Account account)
{
    printf(PURPLE "----------- Account Details -----------\n" RESET);
    printf(CYAN "Account ID     : " RESET "%lld\n", account.accountID);
    printf(CYAN "Owner ID       : " RESET "%lld\n", account.ownerID);
    printf(CYAN "Balance        : " RESET "%.2f DH\n", account.balance);
    printf(CYAN "Account Type   : " RESET "%s\n", account.accountType);
    printf(CYAN "Account Status : " RESET "%s\n", account.isBlocked ? RED "Blocked" RESET : GREEN "Active" RESET);
    printf(CYAN "Date Created   : " RESET "%s\n", account.dateCreated);
    printf(PURPLE "---------------------------------------\n" RESET);
}

void displayBankCardInfo(Account account)
{
    BankCard bankCard = searchBankCardByaccountID(account.accountID);

    if (bankCard.cardaccountID == 0)
    {
        printf(RED "No bank card is associated with this account.\n" RESET);
        return;
    }
    printf("\n" PURPLE "------- Bank Card Information -------\n" RESET);
    printf(PURPLE "=====================================\n" RESET);
    printf(CYAN "Cardholder Name : " RESET "%s\n", bankCard.cardHolderName);

    printf(CYAN "Account ID      : " RESET "%lld\n", bankCard.cardaccountID);

    // Mask all but the last 4 digits of the card number
    printf(CYAN "Card Number     : " RESET "**** **** **** %s\n", bankCard.cardNumber + 12);

    printf(CYAN "Card Type       : " RESET "%s\n", bankCard.cardtype);
    printf(CYAN "Expiry Date     : " RESET "%s\n", bankCard.expiryDate);

    printf(CYAN "CVV             : " RESET "%s\n", bankCard.cvv);

    printf(CYAN "Balance         : " RESET "%.2f\n", bankCard.cardbalance);

    printf(CYAN "Card Status     : " RESET "%s\n", bankCard.cardBlocked ? RED "Blocked" RESET : GREEN "Active" RESET);

    printf(PURPLE "=====================================\n" RESET);
}

void displayAllAccounts()
{
    FILE *file = fopen("accounts.dat", "ab");
    if (file == NULL)
    {
        printf(RED "ERROR: Failed to open the accounts file.\n" RESET);
        return;
    }

    Account account;
    int accountCount = 0;

    printf(PURPLE "------------------------- All Accounts -------------------------\n" RESET);
    while (fread(&account, sizeof(Account), 1, file) == 1)
    {
        printf(ORANGE "Account # %d\n" RESET, ++accountCount);
        printf(CYAN "Account ID     : " RESET "%lld\n", account.accountID);
        printf(CYAN "Owner ID       : " RESET "%lld\n", account.ownerID);
        printf(CYAN "Balance        : " RESET "%.2f DH\n", account.balance);
        printf(CYAN "Account Type   : " RESET "%s\n", account.accountType);
        printf(CYAN "Account Status : " RESET "%s\n", account.isBlocked ? RED "Blocked" RESET : GREEN "Active" RESET);
        printf(CYAN "Date Created   : " RESET "%s\n", account.dateCreated);
        printf(YELLOW "-------------------------------------------\n" RESET);
    }

    if (accountCount == 0)
    {
        printf(RED "No accounts found.\n" RESET);
    }
    else
    {
        printf(GREEN "Total Accounts: " RESET "%d\n", accountCount);
    }

    fclose(file);
    return;
}
