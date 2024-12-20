#include "account.h"

void displayAccountDetails(Account account)
{
    setCursor(2, 40);
    printf(PURPLE "----------- Account Details -----------\n" RESET);
    setCursor(3, 40);
    printf(CYAN "Account ID     : " RESET "%lld\n", account.accountID);
    setCursor(4, 40);
    printf(CYAN "Owner ID       : " RESET "%lld\n", account.ownerID);
    setCursor(5, 40);
    printf(CYAN "Balance        : " RESET "%.2f DH\n", account.balance);
    setCursor(6, 40);
    printf(CYAN "Account Type   : " RESET "%s\n", account.accountType);
    setCursor(7, 40);
    printf(CYAN "Account Status : " RESET "%s\n", account.isBlocked ? RED "Blocked" RESET : GREEN "Active" RESET);
    setCursor(8, 40);
    printf(CYAN "Date Created   : " RESET "%s\n", account.dateCreated);
    setCursor(9, 40);
    printf(PURPLE "---------------------------------------\n" RESET);
}

void displayBankCardInfo(Account account)
{
    BankCard bankCard = searchBankCardByaccountID(account.accountID);

    if (bankCard.cardaccountID == 0)
    {
        printf(RED "\t\tNo bank card is associated with this account.\n" RESET);
        return;
    }
    printf("\n");
    setCursor(2, 40);
    printf(PURPLE "------- Bank Card Information -------\n" RESET);
    setCursor(3, 40);
    printf(PURPLE "=====================================\n" RESET);
    setCursor(4, 40);
    printf(CYAN "Cardholder Name : " RESET "%s\n", bankCard.cardHolderName);
    setCursor(5, 40);
    printf(CYAN "Account ID      : " RESET "%lld\n", bankCard.cardaccountID);
    setCursor(6, 40);
    // Mask all but the last 4 digits of the card number
    printf(CYAN "Card Number     : " RESET "**** **** **** %s\n", bankCard.cardNumber + 12);
    setCursor(7, 40);
    printf(CYAN "Card Type       : " RESET "%s\n", bankCard.cardtype);
    setCursor(8, 40);
    printf(CYAN "Expiry Date     : " RESET "%s\n", bankCard.expiryDate);
    setCursor(9, 40);
    printf(CYAN "CVV             : " RESET "%s\n", bankCard.cvv);
    setCursor(10, 40);
    printf(CYAN "Balance         : " RESET "%.2f\n", bankCard.cardbalance);
    setCursor(11, 40);
    printf(CYAN "Card Status     : " RESET "%s\n", bankCard.cardBlocked ? RED "Blocked" RESET : GREEN "Active" RESET);
    setCursor(12, 40);
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

void displayFilteredAccounts(int filterType, int filterValue) { // 1: Activation  0: blacklist
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        perror("ERROR: Failed to open account file");
        printf("Unable to access the account database.\nPlease report this issue to the technical team for resolution.\n");
        return;
    }

    Account account;
    int count = 0;

    // Determine filter descriptions
    char *filterTypeDescription = filterType ? "\033[1;36mActivation    \033[0m" : "\033[1;31mBlocked Status\033[0m";
    char *filterValueDescription = filterType 
                                   ? (filterValue ? "\033[1;32mActive     \033[0m" : "\033[1;33mInactive   \033[0m")
                                   : (filterValue ? "\033[1;31mBlocked    \033[0m" : "\033[1;32mNot Blocked\033[0m");

    printf(PURPLE"\n+------ Filtered Accounts ("RESET"%s: %s"PURPLE") ---------+\n"RESET, filterTypeDescription, filterValueDescription);
    printf(PURPLE "|" RESET ORANGE " %-5s " RESET PURPLE"|" RESET ORANGE " %-15s "RESET PURPLE"|"RESET ORANGE" %-10s "RESET PURPLE"|"RESET ORANGE" %-23s "RESET PURPLE"|\n", "No", "Account ID", "Balance", "Date Created");
    printf(PURPLE"+----------------------------------------------------------------+\n" RESET);

    while (fread(&account, sizeof(Account), 1, file) == 1) {
        // Filter logic
        if (((filterType && filterValue) && (account.isActive == 1)) ||  // Active accounts
            ((filterType && !filterValue) && (account.isActive == 0)) || // Inactive accounts
            ((!filterType && filterValue) && (account.isBlocked == 1)) || // Blocked accounts
            ((!filterType && !filterValue) && (account.isBlocked == 0)))  // Not blocked accounts
        {
            count++;
            printf(PURPLE"|"RESET CYAN" %-5d "RESET PURPLE"|"RESET" %-15lld "PURPLE"|"RESET" %-10.2f "PURPLE"|"RESET" %-23s "PURPLE"|\n"RESET,
                   count,
                   account.accountID,
                   account.balance,
                   account.dateCreated);
        }
    }

    fclose(file);

    if (count == 0) {
        printf(PURPLE"|                                                                |\n"RESET);
        printf(PURPLE"|"RESET RED "\t\tNo matching accounts found.                      "RESET PURPLE"|\n"RESET);
        printf(PURPLE"|                                                                |\n"RESET);
        printf(PURPLE"+----------------------------------------------------------------+\n" RESET);
    } else {
        printf(PURPLE"+----------------------------------------------------------------+\n" RESET);
        printf(GREEN"Displayed "RESET BOLD"%d"RESET GREEN" account(s) successfully."RESET, count);
    }
}