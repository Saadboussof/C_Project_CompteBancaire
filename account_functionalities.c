#include "account.h"

int payOnline(Account *account, float amount) 
{
    if (account->balance < amount) {
        printf(RED "Transaction failed: Insufficient funds.\n" RESET);
        return 0; // Payment failed
    }

    // Deduct the amount from the card balance
    account->balance -= amount;
    updateAccount(account); // Update account file

    printf(GREEN "Payment of %.2f was successful! Remaining balance: %.2f\n" RESET, amount, account->balance);
    return 1; // Payment successful
}

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