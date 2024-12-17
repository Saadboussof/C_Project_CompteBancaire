#include "account.h"

#define MAX_CATEGORIES 20 //max number of payment categories

int rechargeOnline(Account *account)
{
    char *TELECOM_PROVIDERS[] = {"Inwi", 
                                 "Orange", 
                                 "Maroc Telecom", 
                                 NULL};
    char *RECHARGE_AMOUNTS[] = {"5 DH", 
                                "10 DH", 
                                "20 DH", 
                                "50 DH", 
                                "100 DH", 
                                "200 DH", 
                                "500 DH", 
                                "Other", 
                                NULL};
    char *RECHARGE_TYPES[] = {"*1", 
                              "*2", 
                              "*3", 
                              "*6", 
                              "*25", 
                              "Normal", 
                              NULL};

    char phoneNumber[11] = "";
    int amount;

    Client *linkedClient = findClient("0", account->ownerID, 0);
    printf("Linked phone number found: " GREEN "%s\n" RESET, linkedClient->phoneNumber);
    printf(ORANGE "Do you want to recharge this number? (y/n): " RESET);
    
    char response[2];
    scanf("%1s", response);
    response[0] = tolower(response[0]);     // Convert to lowercase
    
    if (strcmp(response, "y") == 0) 
    {
        strcpy(phoneNumber, linkedClient->phoneNumber);
    } else {
        printf(CYAN "Enter the phone number you want to recharge: " RESET);
        scanf("%10s", phoneNumber);
    }

    // Step 1: Choose telecom provider
    int providerIndex = choose_item(TELECOM_PROVIDERS, "Choose Telecom Provider");
    printf(GREEN "Selected provider: %s\n" RESET, TELECOM_PROVIDERS[providerIndex]);

    // Step 2: Choose recharge amount
    int amountIndex = choose_item(RECHARGE_AMOUNTS, "Choose Recharge Amount");

    switch (amountIndex)
    {
        case 0:
            amount = 5;
            break;
        case 1:
            amount = 10;
            break;
        case 2:
            amount = 20;
            break;
        case 3:
            amount = 50;
            break;
        case 4:
            amount = 100;
            break;
        case 5:
            amount = 200;
            break;
        case 6:
            amount = 500;
            break;
        default:
            printf(ORANGE "Entre the amount of recharge: " RESET);
            scanf("%d", &amount);
            break;
    }

    if (account->balance < (float)amount) 
    {
        printf(RED "Recharge failed: Insufficient funds.\n" RESET);
        return 0; // Recharge failed
    }
    hestoric data;
    data.AccountID = account->accountID ;
    data.amount = -amount ;
    strcpy(data.detail,"you did a Recharge") ;
    getCurrentDate(data.dateop, sizeof(data.dateop));
    savehesto(data);
    // Step 3: Choose recharge type
    int rechargeTypeIndex = choose_item(RECHARGE_TYPES, "Choose Recharge Type");
    printf(GREEN "Selected recharge type: %s\n" RESET, RECHARGE_TYPES[rechargeTypeIndex]);

    // Step 4: Deduct the amount from the card balance and update
    account->balance -= (float)amount;
    updateAccount(account);
    printf(GREEN "Recharge successful!\n" RESET);
    printf("Details:\n");
    printf(PURPLE "Phone Number   : " RESET "%s\n", phoneNumber);
    printf(PURPLE "Recharge Amount: " RESET "%d\n", amount);
    printf(PURPLE "Recharge Type  : " RESET "%s\n", RECHARGE_TYPES[rechargeTypeIndex]);

    printf(CYAN "Remaining balance: " RESET "%.2f\n", account->balance);
    return 1; // Recharge successful
}
<<<<<<< HEAD
typedef struct {
    char name[30];
    float totalSpent;
    float budget;
} Category;
typedef struct {
    char description[50];
    char category[30];
    float amount;
} Transaction;

Category categories[MAX_CATEGORIES];
int categoryCount = 5;

// Initialize Categories with Specific Purposes
void initializeCategories() {
    strcpy(categories[0].name, "Groceries");
    categories[0].budget = 200.0;

    strcpy(categories[1].name, "Bills");
    categories[1].budget = 500.0;

    strcpy(categories[2].name, "Entertainment");
    categories[2].budget = 100.0;

    strcpy(categories[3].name, "Transportation");
    categories[3].budget = 150.0;

    strcpy(categories[4].name, "Others");
    categories[4].budget = 50.0;

    for (int i = 0; i < categoryCount; i++) {
        categories[i].totalSpent = 0.0;
    }
}

char *Categories[] = {
    "Groceries",
    "Bills",
    "Entertainment",
    "Transportation",
    "Others",
    "Add new categorie",
    NULL};

void payOnline(Account *account) {
    BankCard cardpayment = searchBankCardByaccountID(account->accountID);

    char description[50];
    float amount;
    int categoryChoice;

    printf("Enter the amount to pay : DH ");
    scanf("%f", &amount);

    if (amount > cardpayment.cardbalance) {
        printf(RED "Insufficient funds! Payment cannot be processed.\n" RESET);
        return;
    }

    int choice = choose_item(Categories, "Select a category");

    if (amount > categories[choice].budget - categories[choice].totalSpent) {
        printf(RED "You're out of the categorie %s's budget.\n" RESET , categories[choice]);
        return;
    }

    printf("Enter a description for this payment: ");
    scanf(" %[^\n]", description);

    // Deduct from card balance and update category spending
    cardpayment.cardbalance -= amount;
    categories[choice].totalSpent += amount;

    // Transaction transaction;             FIXME: // it gonna be the history struct and its functions 
    // // Record the transaction
    // strcpy(transactions[transactionCount].description, description);
    // strcpy(transactions[transactionCount].category, categories[selectedCategory].name);
    // transactions[transactionCount].amount = amount;
    // transactionCount++;

    printf(GREEN "Payment of %.2fDH for '%s' categorized as '%s' has been processed successfully.\n" RESET , amount, description, categories[choice].name);

    // Perform category-specific action
    handleCategorySpecificAction(choice);
}

// Perform Category-Specific Actions
void handleCategorySpecificAction(int choice) {
    switch (choice)
    {
    case 0:
        printf(CYAN "\n** Tip: Buying in bulk could save you money! **\n" RESET);
        break;
    case 1:
        printf(CYAN "\n** Set up recurring payments for your convenience. **\n" RESET);
        break;
    case 2:
        printf(CYAN "\n** Reminder: Stay within your entertainment budget for savings. **\n" RESET);
        break;
    case 3:
        printf(CYAN "\n** Did you know? Tracking your mileage could help optimize fuel costs. **\n" RESET);
        break;
    case 4:
        printf(CYAN "\n** Note: Record any special details about this payment for future reference. **\n" RESET);
        break;
    default:
        break;
    }
}
=======

char *Choicess[] = {
    " display informations ",
    " recharge online ! ",
    " payer votre facture ",
    " afficher les chiffres de carte ",
    " transaction ",
    " historical of your activities ",
    " return ",
    " exit ",
    NULL};

void FUNCTION(Account selectedAccount){
    while(1) {
        int choice = choose_item(Choicess, " ---- Make your choice ! ---- ");
        switch (choice) {
            case 0:
            displayBankCardInfo(selectedAccount);
            continue;
            
            case 1:
            rechargeOnline(&selectedAccount);
            continue;
            
            case 2:
            printf(" you have not established any relationship with any of your invoices . \n");
            printf(" !!!!!! \n\n ");
            break;
            
            case 3:
            printf(" _________ Your number card is : _________ \n");
            BankCard bankCard = searchBankCardByaccountID(selectedAccount.accountID);
            printf(" \n");
            formatString( bankCard.cardNumber );
            continue;
            
            case 4:
            long long ID ;
            Account *distAccount ;
                while( 1 ) {
                    printf(" give the ID o the account you want to send money to : ");
                    scanf("%lld",&ID);

                    distAccount = searchAccountByID(ID);
                    if( distAccount == NULL ) {
                        printf(" the account does not exist in databases !! \n try again !! \n\n\n");
                    } else break ;
                }
            
            printf("\n how much you want to sent ? : ");
            float much ;
            scanf("%f",&much);
            if( selectedAccount.balance < much ){
                printf(" you have not enough money in your account !! \n\n\n");
            }else{
                selectedAccount.balance = selectedAccount.balance - much ;
                distAccount->balance = distAccount->balance + much ;
                updateAccount(distAccount);
                updateAccount(&selectedAccount);
                hestoric data;
                data.AccountID = selectedAccount.accountID ;
                data.amount = -much ;
                strcpy(data.detail," ---->> you send money !! :") ;
                getCurrentDate(data.dateop, sizeof(data.dateop));
                savehesto(data);

                data.AccountID = distAccount->accountID ;
                data.amount = much ;
                strcpy(data.detail,"---->> you recieve money !! :") ;
                getCurrentDate(data.dateop, sizeof(data.dateop));
                savehesto(data);
            }
            continue;
            
            case 5: 
            searchByAccountID(selectedAccount.accountID);
            printf("\n\n");
            continue;
            
            case 6:
                logIn_Account(selectedAccount.ownerID);
            
            default:
                exit(0);
            continue;
        }
    }
}
>>>>>>> origin/master
