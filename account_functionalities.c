#include "account.h"

#define MAX_CATEGORIES 20 // max number of payment categories

// int rechargeOnline(Account *account)
// {
//     char *TELECOM_PROVIDERS[] = {"Inwi",
//                                  "Orange",
//                                  "Maroc Telecom",
//                                  NULL};
//     char *RECHARGE_AMOUNTS[] = {"5 DH",
//                                 "10 DH",
//                                 "20 DH",
//                                 "50 DH",
//                                 "100 DH",
//                                 "200 DH",
//                                 "500 DH",
//                                 "Other",
//                                 NULL};
//     char *RECHARGE_TYPES[] = {"*1",
//                               "*2",
//                               "*3",
//                               "*6",
//                               "*25",
//                               "Normal",
//                               NULL};

//     char phoneNumber[11] = "";
//     int amount;

//     Client *linkedClient = findClient("0", account->ownerID, 0);
//     printf("Linked phone number found: " GREEN "%s\n" RESET, linkedClient->phoneNumber);
//     printf(ORANGE "Do you want to recharge this number? (y/n): " RESET);

//     char response[2];
//     scanf("%1s", response);
//     response[0] = tolower(response[0]); // Convert to lowercase

//     if (strcmp(response, "y") == 0)
//     {
//         strcpy(phoneNumber, linkedClient->phoneNumber);
//     }
//     else
//     {
//         printf(CYAN "Enter the phone number you want to recharge: " RESET);
//         scanf("%10s", phoneNumber);
//     }

//     // Step 1: Choose telecom provider
//     int providerIndex = choose_item(TELECOM_PROVIDERS, "Choose Telecom Provider");
//     printf(GREEN "Selected provider: %s\n" RESET, TELECOM_PROVIDERS[providerIndex]);

//     // Step 2: Choose recharge amount
//     int amountIndex = choose_item(RECHARGE_AMOUNTS, "Choose Recharge Amount");

//     switch (amountIndex)
//     {
//     case 0:
//         amount = 5;
//         break;
//     case 1:
//         amount = 10;
//         break;
//     case 2:
//         amount = 20;
//         break;
//     case 3:
//         amount = 50;
//         break;
//     case 4:
//         amount = 100;
//         break;
//     case 5:
//         amount = 200;
//         break;
//     case 6:
//         amount = 500;
//         break;
//     default:
//         printf(ORANGE "Entre the amount of recharge: " RESET);
//         scanf("%d", &amount);
//         break;
//     }

//     if (account->balance < (float)amount)
//     {
//         printf(RED "Recharge failed: Insufficient funds.\n" RESET);
//         return 0; // Recharge failed
//     }
//     hestoric data;
//     data.AccountID = account->accountID;
//     data.amount = -amount;
//     strcpy(data.detail, "you did a Recharge");
//     getCurrentDate(data.dateop, sizeof(data.dateop));
//     savehesto(data);
//     // Step 3: Choose recharge type
//     int rechargeTypeIndex = choose_item(RECHARGE_TYPES, "Choose Recharge Type");
//     printf(GREEN "Selected recharge type: %s\n" RESET, RECHARGE_TYPES[rechargeTypeIndex]);

//     // Step 4: Deduct the amount from the card balance and update
//     account->balance -= (float)amount;
//     updateAccount(account);
//     printf(GREEN "Recharge successful!\n" RESET);
//     printf("Details:\n");
//     printf(PURPLE "Phone Number   : " RESET "%s\n", phoneNumber);
//     printf(PURPLE "Recharge Amount: " RESET "%d\n", amount);
//     printf(PURPLE "Recharge Type  : " RESET "%s\n", RECHARGE_TYPES[rechargeTypeIndex]);

//     printf(CYAN "Remaining balance: " RESET "%.2f\n", account->balance);
//     return 1; // Recharge successful
// }
void printHeader(const char *title)
{
    printf("\n" CYAN "=================================================\n" RESET);
    printf(GREEN "                   %s                    \n" RESET, title);
    printf(CYAN "=================================================\n" RESET);
}

// Fonction pour afficher un menu avec possibilité de retour
int choose_item_with_return(char *items[], const char *message)
{
    int i, choice;
    printf("\n" ORANGE "%s:\n" RESET, message);
    for (i = 0; items[i] != NULL; i++)
    {
        printf(GREEN " [%d] %s\n" RESET, i + 1, items[i]);
    }
    printf(RED " [0] Return\n" RESET); // Option pour revenir en arrière
    printf(ORANGE "Enter your choice: " RESET);
    scanf("%d", &choice);

    if (choice == 0)
    {
        printf(RED "Operation cancelled. Returning to the main menu...\n" RESET);
        return -1; // Indiquer un retour
    }
    return choice - 1; // Retourner l'index sélectionné
}

int rechargeOnline(Account *account)
{
    char *TELECOM_PROVIDERS[] = {"Inwi", "Orange", "Maroc Telecom", NULL};
    char *RECHARGE_AMOUNTS[] = {"5 DH", "10 DH", "20 DH", "50 DH", "100 DH", "200 DH", "500 DH", "Other", NULL};
    char *RECHARGE_TYPES[] = {"*1", "*2", "*3", "*6", "*25", "Normal", NULL};

    char phoneNumber[11] = "";
    int amount;

    Client *linkedClient = findClient("0", account->ownerID, 0);
    printHeader("Recharge Your Phone");

    // Étape 1: Obtenir le numéro de téléphone
    printf("Linked phone number found: " GREEN "%s\n" RESET, linkedClient->phoneNumber);
    printf(ORANGE "Do you want to recharge this number? (y/n): " RESET);

    char response[2];
    scanf("%1s", response);
    response[0] = tolower(response[0]);

    if (strcmp(response, "y") == 0)
    {
        strcpy(phoneNumber, linkedClient->phoneNumber);
    }
    else
    {
        printf(CYAN "Enter the phone number you want to recharge: " RESET);
        scanf("%10s", phoneNumber);
    }

    // Étape 2: Choisir le fournisseur
    int providerIndex = choose_item(TELECOM_PROVIDERS, "Choose Telecom Provider");
    if (providerIndex == -1) return 0;

    printf(GREEN "Selected provider: %s\n" RESET, TELECOM_PROVIDERS[providerIndex]);

    // Étape 3: Choisir le montant de la recharge
    int amountIndex = choose_item(RECHARGE_AMOUNTS, "Choose Recharge Amount");
    if (amountIndex == -1) return 0;

    switch (amountIndex)
    {
    case 0: amount = 5; break;
    case 1: amount = 10; break;
    case 2: amount = 20; break;
    case 3: amount = 50; break;
    case 4: amount = 100; break;
    case 5: amount = 200; break;
    case 6: amount = 500; break;
    default:
        printf(ORANGE "Enter the amount of recharge: " RESET);
        scanf("%d", &amount);
        break;
    }

    // Vérifier si le solde est suffisant
    if (account->balance < (float)amount)
    {
        printf(RED "Recharge failed: Insufficient funds.\n" RESET);
        return 0;
    }

    // Étape 4: Choisir le type de recharge
    int rechargeTypeIndex = choose_item(RECHARGE_TYPES, "Choose Recharge Type");
    if (rechargeTypeIndex == -1) return 0;

    printf(GREEN "Selected recharge type: %s\n" RESET, RECHARGE_TYPES[rechargeTypeIndex]);

    // Étape 5: Confirmer avant la déduction
    printf("\n" CYAN "You are about to recharge:\n" RESET);
    printf(GREEN "Phone Number   : %s\n" RESET, phoneNumber);
    printf(GREEN "Recharge Amount: %d DH\n" RESET, amount);
    printf(GREEN "Recharge Type  : %s\n" RESET, RECHARGE_TYPES[rechargeTypeIndex]);
    printf(RED "Do you confirm? (y/n): " RESET);
    scanf("%1s", response);

    if (tolower(response[0]) != 'y')
    {
        printf(RED "Operation cancelled.\n" RESET);
        return 0;
    }

    // Étape 6: Déduire le montant du solde
    account->balance -= (float)amount;
    updateAccount(account);

    // Enregistrer l'historique
    hestoric data;
    data.AccountID = account->accountID;
    data.amount = -amount;
    strcpy(data.detail, "you did a Recharge");
    getCurrentDate(data.dateop, sizeof(data.dateop));
    savehesto(data);

    // Affichage des détails finaux
    printf("\n" GREEN "Recharge successful!\n" RESET);
    printf(BLUE "====================================\n" RESET);
    printf(PURPLE "Phone Number   : " RESET "%s\n", phoneNumber);
    printf(PURPLE "Recharge Amount: " RESET "%d DH\n", amount);
    printf(PURPLE "Recharge Type  : " RESET "%s\n", RECHARGE_TYPES[rechargeTypeIndex]);
    printf(PURPLE "Remaining Balance: " RESET "%.2f DH\n", account->balance);
    printf(BLUE "====================================\n\n" RESET);

    return 1; // Recharge réussie
}

char *Choicess[] = {
    "Display info",
    "Online recharge",
    "Fact pay",
    "Card number",
    "Transaction",
    "History",
    "transfertcard",
    "Return",
    "Exit",
    NULL};

void FUNCTION(Account selectedAccount)
{
    while (1)
    {
        int choice = choose_item(Choicess, " ---- Make your choice ! ---- ");
        switch (choice)
        {
        case 0:
            displayBankCardInfo(selectedAccount);
            continue;

        case 1:
            rechargeOnline(&selectedAccount);
            continue;

        case 2:
            // printf(RED" you have not established any relationship with any of your invoices . \n"RESET);
            // printf("");
            // printf(" !!!!!! \n\n ");
            payBills(&selectedAccount);
            break;

        case 3:
            printf("\033[1;34m _________ Your number card is : _________ \033[0m\n");
            BankCard bankCard = searchBankCardByaccountID(selectedAccount.accountID);
            printf(" \n");
            formatString(bankCard.cardNumber);
            continue;

        case 4:
            long long ID;
            Account *distAccount;
            int i = 0 ;
            while (1)
            {
                printf(" give the ID o the account you want to send money to : ");
                scanf("%lld", &ID);

                distAccount = searchAccountByID(ID);
                if (distAccount == NULL)
                {
                   printf(" the account does not exist in databases !! \n try again !! \n\n\n");
                }
                else break;
                i++ ;
                if( i == 3 ) break ;
            }
            if( i == 3 ) continue;
            printf("\n how much you want to sent ? : ");
            float much;
            scanf("%f", &much);
            if (selectedAccount.balance < much)
            {
                printf(" you have not enough money in your account !! \n\n\n");
            }
            else
            {
                selectedAccount.balance = selectedAccount.balance - much;
                distAccount->balance = distAccount->balance + much;
                updateAccount(distAccount);
                updateAccount(&selectedAccount);
                hestoric data;
                data.AccountID = selectedAccount.accountID;
                data.amount = -much;
                strcpy(data.detail, " ->> you send money !! :");
                getCurrentDate(data.dateop, sizeof(data.dateop));
                savehesto(data);

                data.AccountID = distAccount->accountID;
                data.amount = much;
                strcpy(data.detail, "->> you recieve money !! :");
                getCurrentDate(data.dateop, sizeof(data.dateop));
                savehesto(data);
            }
            continue;

        case 5:
            searchByAccountID(selectedAccount.accountID);
            printf("\n\n");
            continue;
        case 6:{
            // Transfer balance to card
            BankCard bankCard = searchBankCardByaccountID(selectedAccount.accountID);
            if (bankCard.cardaccountID == 0) {
                printf(RED "No bank card is associated with this account.\n" RESET);
                continue;
            }
            transferBalanceToCard(&selectedAccount, &bankCard);
            continue;
        }
        case 7:
            logIn_Account(selectedAccount.ownerID);

        default:
            exit(0);
            continue;
        }
    }
}
void transferBalanceToCard(Account *account, BankCard *bankCard) {
    printf("\n\033[1;36m------ Transfer Balance to Card ------\033[0m\n");
    printf("\033[1;35mYour current account balance: %.2f DH\033[0m\n", account->balance);

    if (account->balance <= 0) {
        printf("\033[1;31mError: Insufficient account balance to transfer!\033[0m\n");
        return;
    }

    float transferAmount;
    while (1) {
        printf("\033[1;34mEnter the amount to transfer to your card: \033[0m");
        scanf("%f", &transferAmount);

        if (transferAmount <= 0 || transferAmount > account->balance) {
            printf("\033[1;31mInvalid amount. Please enter a valid amount less than or equal to your account balance.\033[0m\n");
        } else {
            break;
        }
    }
    // Deduct amount from account balance and add to card balance
    account->balance -= transferAmount;
    bankCard->cardbalance += transferAmount;

    // Update both the account and bank card in the database
    updateAccount(account);
    updateBankCard(bankCard);

    // Log the transaction in history
    hestoric data;
    data.AccountID = account->accountID;
    data.amount = -transferAmount;
    strcpy(data.detail, "-> Transferred balance to card.");
    getCurrentDate(data.dateop, sizeof(data.dateop));
    savehesto(data);

    printf("\n\033[1;32mSuccess: %.2f DH has been transferred to your card.\033[0m\n", transferAmount);
    printf("\033[1;34mUpdated Account Balance: %.2f DH\n\033[0m", account->balance);
    printf("\033[1;34mUpdated Card Balance: %.2f DH\n\033[0m", bankCard->cardbalance);
}
void logPaidBill(long long accountID, int billID) {
    char filename[50];
    sprintf(filename, "paid_bills_%lld.txt", accountID);

    FILE *file = fopen(filename, "a"); // Append to the file
    if (!file) {
        printf("\033[1;31mError: Unable to log the paid bill!\033[0m\n");
        return;
    }
    fprintf(file, "%d\n", billID); // Log the bill ID
    fclose(file);
}

int isBillPaid(long long accountID, int billID) {
    char filename[50];
    sprintf(filename, "paid_bills_%lld.txt", accountID);

    FILE *file = fopen(filename, "r");
    if (!file) {
        return 0; // If file doesn't exist, no bills are paid yet
    }

    int id;
    while (fscanf(file, "%d", &id) == 1) {
        if (id == billID) {
            fclose(file);
            return 1; // Bill is already paid
        }
    }
    fclose(file);
    return 0;
}

void payBills(Account *selectedAccount) {
    // Static list of predefined bills
    Facture factures[] = {
        {19482, "Water", 50.00},
        {29301, "Electricity", 100.00},
        {38491, "Wifi", 60.00},
        {47281, "Car Insurance", 200.00}
    };
    int numFactures = sizeof(factures) / sizeof(factures[0]);

    while (1) {
        // Display unpaid bills
        printf("\n\033[1;36m========== Available Bills to Pay ==========\033[0m\n");
        printf("\033[1;33m+---------+------------------+-------------+\033[0m\n");
        printf("\033[1;33m|   ID    |       Name       |   Amount DH |\033[0m\n");
        printf("\033[1;33m+---------+------------------+-------------+\033[0m\n");

        int availableBills = 0;
        for (int i = 0; i < numFactures; i++) {
            if (factures[i].id != 0 && !isBillPaid(selectedAccount->accountID, factures[i].id)) {
                printf("\033[1;32m| %7d | %-16s | %10.2f DH |\033[0m\n",
                       factures[i].id, factures[i].name, factures[i].amount);
                availableBills++;
            }
        }
        printf("\033[1;33m+---------+------------------+-------------+\033[0m\n");

        // If no bills are left to pay
        if (availableBills == 0) {
            printf("\033[1;32mAll bills are paid! No bills available.\033[0m\n");
            return;
        }

        printf("\033[1;35mEnter 0 to return to the previous page.\033[0m\n");

        // Input: User selects a bill by ID
        char enteredInput[10];
        printf("\n\033[1;35mEnter the ID of the bill you want to pay: \033[0m");
        scanf("%s", enteredInput);

        // Validate input
        int isNumeric = 1;
        for (int i = 0; enteredInput[i] != '\0'; i++) {
            if (enteredInput[i] < '0' || enteredInput[i] > '9') {
                isNumeric = 0;
                break;
            }
        }

        if (!isNumeric) {
            printf("\033[1;31mError: Invalid input! Please enter a valid numeric ID.\033[0m\n");
            continue;
        }

        int enteredID = atoi(enteredInput);
        if (enteredID == 0) {
            printf("\033[1;33mReturning to the previous menu...\033[0m\n");
            return;
        }

        // Search for the facture by ID
        Facture *selectedFacture = NULL;
        for (int i = 0; i < numFactures; i++) {
            if (factures[i].id == enteredID) {
                selectedFacture = &factures[i];
                break;
            }
        }

        if (!selectedFacture || selectedFacture->id == 0 || isBillPaid(selectedAccount->accountID, enteredID)) {
            printf("\033[1;31mError: Invalid or already paid bill ID!\033[0m\n");
            continue;
        }

        // Check if the account has sufficient balance
        if (selectedAccount->balance < selectedFacture->amount) {
            printf("\033[1;31mInsufficient funds to pay for %s (%.2f DH)!\033[0m\n",
                   selectedFacture->name, selectedFacture->amount);
            continue;
        }

        // Deduct the amount and update balance
        selectedAccount->balance -= selectedFacture->amount;
        updateAccount(selectedAccount);

        // Log the transaction
        hestoric data;
        data.AccountID = selectedAccount->accountID;
        data.amount = -selectedFacture->amount;
        snprintf(data.detail, sizeof(data.detail), "Paid bill: %s", selectedFacture->name);
        getCurrentDate(data.dateop, sizeof(data.dateop));
        savehesto(data);

        // Log the bill as paid
        logPaidBill(selectedAccount->accountID, enteredID);

        printf("\n\033[1;32mSuccess: You have paid for %s (%.2f DH).\033[0m\n",
               selectedFacture->name, selectedFacture->amount);
        printf("\033[1;34mRemaining Balance: %.2f DH\n\033[0m", selectedAccount->balance);
    }
}
