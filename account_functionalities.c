#include "account.h"

#define MAX_CATEGORIES 20 // max number of payment categories

void printHeader(const char *title)
{
    printf("\n" CYAN "=================================================\n" RESET);
    printf(GREEN "              %s                    \n" RESET, title);
    printf(CYAN "=================================================\n" RESET);
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
    printf("\n--> Linked phone number found: " BOLD "%s\n" RESET, linkedClient->phoneNumber);
    printf(ORANGE "\nDo you want to recharge this number? (y/n): " RESET);

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

    printf("Selected provider: " GREEN "%s\n" RESET, TELECOM_PROVIDERS[providerIndex]);

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

    printf("Selected recharge type: " GREEN "%s\n" RESET, RECHARGE_TYPES[rechargeTypeIndex]);

    // Étape 5: Confirmer avant la déduction
    printf("\n" YELLOW "You are about to recharge :\n" RESET);
    printf("Phone Number   : %s\n", phoneNumber);
    printf("Recharge Amount: %d DH\n", amount);
    printf("Recharge Type  : %s\n", RECHARGE_TYPES[rechargeTypeIndex]);
    printf(CYAN "Do you want confirm? (y/n): " RESET);
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
    printf(BOLD "\n====================================\n" RESET);
    printf("Phone Number   : %s\n", phoneNumber);
    printf("Recharge Amount: %d DH\n", amount);
    printf("Recharge Type  : %s\n", RECHARGE_TYPES[rechargeTypeIndex]);
    printf(BOLD "====================================\n\n" RESET);
    printf("\nRemaining Balance: %.2f DH\n", account->balance);

    return 1; // Recharge réussie
}

char *Choicess[] = {
    "Display card info",
    "Online recharge",
    "Facture payment",
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
        int choice = choose_item(Choicess, "Account functionalities");
        switch (choice)
        {
        case 0:
            displayBankCardInfo(selectedAccount);
            continue;

        case 1:
            rechargeOnline(&selectedAccount);
            continue;

        case 2:
            payBills(&selectedAccount);
            break;

        case 3:
            printf(BLUE "\n\t\t_________ Your number card is : _________ \n" RESET);
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
                printf("\nGive the ID of the account you want to send money to : ");
                scanf("%lld", &ID);

                distAccount = searchAccountByID(ID);
                if (distAccount == NULL)
                {
                   printf(RED "The account does not exist in databases !!\n" RESET "try again");
                   system("cls");
                   fordelay(1500000000);
                   printf(ORANGE "Attempt %d/3"RESET, i+1);
                }
                else break;
                i++ ;
                if( i == 3 ) break ;
            }
            if( i == 3 ) continue;
            printf("\nHow much do you want to sent ? : ");
            float much;
            scanf("%f", &much);
            if (selectedAccount.balance < much)
            {
                printf("You don't have enough money in your account !! \n\n\n");
            }
            else
            {
                printf(GREEN"Operation succesful\n"RESET);
                printf("You send an amount of "BOLD"%2.f"RESET" to the account "BOLD"%lld\n"RESET, much, ID);
                selectedAccount.balance = selectedAccount.balance - much;
                distAccount->balance = distAccount->balance + much;
                updateAccount(distAccount);
                updateAccount(&selectedAccount);
                hestoric data;
                data.AccountID = selectedAccount.accountID;
                data.amount = -much;
                strcpy(data.detail, "You send money");
                getCurrentDate(data.dateop, sizeof(data.dateop));
                savehesto(data);

                data.AccountID = distAccount->accountID;
                data.amount = much;
                strcpy(data.detail, "You recieve money");
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
                printf(RED "\tNo bank card is associated with this account.\n" RESET);
                continue;
            }
            transferBalanceToCard(&selectedAccount, &bankCard);
            continue;
        }

        case 7:
            BankCard bkCard = searchBankCardByaccountID(selectedAccount.accountID);
            if (bkCard.cardaccountID == 0) {
                printf(RED "No bank card is associated with this account.\n" RESET);
            }
            handleCardBlocking(&bkCard);
            continue;

        case 8:
            logIn_Account(selectedAccount.ownerID);

        default:
            exit(0);
            continue;
        }
    }
}

void transferBalanceToCard(Account *account, BankCard *bankCard) {
    printf(CYAN "\n------ Transfer Balance to Card ------\n\n" RESET);
    printf("Your current account balance: " BOLD "%.2f DH\n" RESET, account->balance);

    if (account->balance <= 0) {
        printf(RED "Error: Insufficient account balance to transfer!\n" RESET);
        return;
    }

    float transferAmount;
    char choice;

    while (1) {
        printf("Enter the amount to transfer to your card: ");
        scanf("%f", &transferAmount);

        if (transferAmount <= 0 || transferAmount > account->balance) {
            printf(RED "Invalid amount.\n" RESET "Please enter a valid amount less than or equal to your account balance.\n");
            printf("Would you like to try again? (y/n): ");
            choice = getch();
            printf("\n");

            if (choice == 'n' || choice == 'N') {
                printf(ORANGE "Transfer process canceled.\n" RESET);
                return; // Exit the function if the user cancels.
            }
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
    strcpy(data.detail, "Transferred balance to card.");
    getCurrentDate(data.dateop, sizeof(data.dateop));
    savehesto(data);

    printf(GREEN "\nSuccess: %.2f DH has been transferred to your card.\n\n" RESET, transferAmount);
    printf("Updated Account Balance: " BOLD "%.2f DH\n" RESET, account->balance);
    printf("Updated Card Balance: " BOLD "%.2f DH" RESET, bankCard->cardbalance);
}

void logPaidBill(long long accountID, int billID) {
    char filename[50];
    sprintf(filename, "paid_bills_%lld.txt", accountID);

    FILE *file = fopen(filename, "a"); // Append to the file
    if (!file) {
        printf(RED "Error: Unable to log the paid bill!\n" RESET);
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
        {47281, "Car Insurance", 200.00},
        {56382, "Netflix", 200.00}
    };
    int numFactures = sizeof(factures) / sizeof(factures[0]);

    while (1) {
        // Display unpaid bills
        printf(CYAN "\n========== Available Bills to Pay ============\n" RESET);
        printf(YELLOW "+---------+------------------+---------------+\n" RESET);
        printf(YELLOW "|   ID    |       Name       |   Amount DH   |\n" RESET);
        printf(YELLOW "+---------+------------------+---------------+\n" RESET);

        int availableBills = 0;
        for (int i = 0; i < numFactures; i++) {
            if (factures[i].id != 0 && !isBillPaid(selectedAccount->accountID, factures[i].id)) {
                printf(YELLOW "|" RESET CYAN " %7d " RESET YELLOW "|" RESET " %-16s " YELLOW "|" RESET" %10.2f DH " YELLOW "|\n" RESET,
                       factures[i].id, factures[i].name, factures[i].amount);
                availableBills++;
            }
        }
        printf(YELLOW "+---------+------------------+---------------+\n" RESET);

        // If no bills are left to pay
        if (availableBills == 0) {
            printf(GREEN "All bills are paid! No bills available.\n" RESET);
            return;
        }

        // Input: User selects a bill by ID
        char enteredInput[10];
        printf(PURPLE "\nEnter the ID of the bill you want to pay (0 To cancel): ");
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
            printf(RED "Error: Invalid input! Please enter a valid numeric ID.\n" RESET);
            continue;
        }

        int enteredID = atoi(enteredInput);
        if (enteredID == 0) {
            printf(YELLOW "Returning to the previous menu...\n" RESET);
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
            printf(RED "\nError: Invalid or already paid bill ID!\n" RESET);
            fordelay(1200000000);
            system("cls");
            continue;
        }

        // Check if the account has sufficient balance
        if (selectedAccount->balance < selectedFacture->amount) {
            printf(RED "\nInsufficient funds to pay for %s (%.2f DH)!" RESET,
                   selectedFacture->name, selectedFacture->amount);
            fordelay(1200000000);
            system("cls");
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

        printf(GREEN "\nSuccess: You have paid for %s (%.2f DH).\n" RESET,
               selectedFacture->name, selectedFacture->amount);
        printf("\nRemaining Balance: " BOLD "%.2f DH" RESET, selectedAccount->balance);
        fordelay(1200000000);
        system("cls");
    }
}
