#include "account.h"

// Select client's account : Log in by PIN if not blocked, New account creation, update profile

void logIn_Account(long long ownerID)
{
    hestoric data ;
    int resultCount = 0;

    Account *accounts = searchAccountsByClientID(ownerID, &resultCount);

    if (resultCount == 0) {
        printf(BLUE "No accounts found. Creating a new account...\n" RESET);
        creatingAccountRequest(ownerID);
        return;
    }

    char **accountOptions = malloc((resultCount + 3) * sizeof(char *));
    if (!accountOptions)
    {
        printf(RED "ERROR : Failed to allocate memory.\n" RESET);
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
    accountOptions[resultCount] = ORANGE "Create new account" RESET;
    accountOptions[resultCount + 1] = CYAN "Update your client profile" RESET;
    accountOptions[resultCount + 2] = NULL;

    int accountSelected = 0;

    while (accountSelected == 0)
    {
        int index_account = choose_item(accountOptions, "Your Accounts ");

        if (index_account == resultCount)
        {
            creatingAccountRequest(ownerID);
            return;
        }
        else if (index_account == resultCount + 1)
        {
            Client *currentaccount = findClient("0", ownerID, 0);
            printf(BLUE "Client profile updating...\n" RESET);
            updateClient(currentaccount->CIN);
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

        if (authenticate_account( &selectedAccount ))
        {
            gradientSpinner(50); // 50 ms per frame

            displayAccountDetails(selectedAccount);
            
            char response[2] ;
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
        
         while(1){
           int choice = choose_item(Choicess, " ---- Make your choice ! ---- ");
           switch (choice)
           {
           case 0:
            displayBankCardInfo(selectedAccount);
            // logIn_Account(ownerID);
            // break;
            continue;
           case 1:
            rechargeOnline(&selectedAccount);
            // logIn_Account(ownerID);
            // break;
            continue;
           case 2:
            printf(" you have not established any relationship with any of your invoices . \n");
            printf(" !!!!!! \n\n ");
            // logIn_Account(ownerID);
            break;
           case 3:
            printf(" _________ Your number card is : _________ \n");
            BankCard bankCard = searchBankCardByaccountID(selectedAccount.accountID);
            // printf("=> %s \n\n",bankCard.cardNumber);
            printf(" \n");
            formatString( bankCard.cardNumber );
            // logIn_Account(ownerID);
            // break;
            continue;
           case 4:
            long long ID ;
            Account *distAccount ;
             while( 1 ){
              printf(" give the ID o the account you want to send money to : ");
              scanf("%lld",&ID);

              distAccount = searchAccountByID(ID);
              if( distAccount == NULL ){
                printf(" the account does not exist in databases !! \n try again !! \n\n\n");
              }else{
                break ;
              }
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
            // logIn_Account(ownerID);
            // break;
            continue;
           case 5: 
            searchByAccountID(selectedAccount.accountID);
            printf("\n\n");
            // logIn_Account(ownerID);
            // break;
            continue;
           case 6:
               logIn_Account(ownerID);
           default:
               exit(0);
            //    break;
            continue;
           }
           }
           
            // printf(ORANGE "Would you like to display your bank card information? (y/n): " RESET);
            // scanf("%1s", response);
            // // Convert input to lowercase for easier comparison
            // response[0] = tolower(response[0]);
            // if (strcmp(response, "y") == 0) displayBankCardInfo(selectedAccount);
            // accountSelected = 1; // Mark account as successfully selected
            // break;
            //rechargeOnline(&selectedAccount); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }

        for (int i = 0; i < resultCount; i++)
        {
            free(accountOptions[i]);
        }
        free(accountOptions);
    }
}
void formatString(char *input) {
    int len = strlen(input);
     printf("==> ");
    for (int i = 0; i < len; i++) {
        printf("%c", input[i]);

        // Insert a space after every 4 characters
        if ((i + 1) % 4 == 0 && i != len - 1) {
            printf(" ");
        }
    }
    printf(" <==\n\n\n");
}

void savehesto(hestoric data) {
    FILE *file = fopen("hestorical.bin", "ab+"); // "ab" = append in binary mode
    if (file == NULL) {
        perror("Error opening file");
    }

    // Write the struct to the file
    fwrite(&data, sizeof(hestoric), 1, file);

    // Close the file
    fclose(file);
    // printf("Data saved successfully.\n");
}
int authenticate_account(Account *selectedAccount)
{
    char PIN[5];
    int failed_attempts = 0;

    while (failed_attempts < GUESSING_LIMIT)
    {
        printf("Enter the PIN of your account: ");
        PIN_hide(PIN, 5);
        if (validatePIN(PIN, selectedAccount->PIN))
        {
            return 1;
        }
        else
        {
            failed_attempts++;
            printf(RED "Incorrect PIN. Please try again.\n" RESET);
        }
    }

    if (failed_attempts == GUESSING_LIMIT)
    {
        handleAccountBlocking(selectedAccount);
        printf(RED "Your account has been blocked due to too many incorrect attempts.\n" RESET);
    }
    return 0;
}

void handleAccountBlocking(Account *account)
{
    account->isBlocked = ~account->isBlocked; // Mark the account as blocked
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
    setAndConfirmPIN(newAccount.PIN);

    // Generate a random account ID and set creation date:
    newAccount.accountID = generateRandomAccountNumber();
    printf("Your account ID: %lld\n", newAccount.accountID);

    getCurrentDate(newAccount.dateCreated, sizeof(newAccount.dateCreated));
    printf("Account created on: %s\n", newAccount.dateCreated);

    // Ask if the client wants a bank card
    requestBankCard(newAccount);

    // Save the request of account creation in the request file:
    saveAccountToFile(&newAccount);

    typingEffect(YELLOW "Request Creation...\n" RESET, 50);
    typingEffect(BLUE "Request Processing...\n" RESET, 50);
    typingEffect(GREEN "Request Submission...\n" RESET, 50);
    printf(BOLD "Done!\n" RESET);

    printf(GREEN "Your account creation request has been submitted successfully!\n" RESET);
}

char *CARD_TYPES[] = {
    "Visa",             // 1111
    "Mastercard",       // 2222
    "American Express", // 3333
    "Discover",         // 4444
    NULL};

void requestBankCard(Account account)
{
    char response[2];
    printf(BLUE "Would you like to request a bank card? (y/n): " RESET);
    scanf("%1s", response);

    // Convert input to lowercase for easier comparison
    response[0] = tolower(response[0]);

    if (strcmp(response, "y") == 0)
    {
        BankCard bankcard;
        // Display card types for the user to choose
        int cardTypeIndex = choose_item(CARD_TYPES, "Choose a card type");
        strcpy(bankcard.cardtype, CARD_TYPES[cardTypeIndex]);

        // Fetch the cardholder's name based on the owner's ID
        Client *client = findClient("0", account.ownerID, 0);
        strcpy(bankcard.cardHolderName, client->name);

        // Calculate expiry date ("expdate" years from the current date)
        char currentDate[23];
        getCurrentDate(currentDate, sizeof(currentDate));
        
        // Extract the year from current date and add "expdate" years to it
        int currentYear = atoi(currentDate);

        int expiryYear = currentYear + expdate;

        // Format expiry date (MM/YY)
        int expiryMonth = atoi(&currentDate[5]); // Extract month from "YYYY-MM-DD"

        snprintf(bankcard.expiryDate, sizeof(bankcard.expiryDate), "%02d/%02d", expiryMonth, expiryYear % 100);

        // Randomly generate CVV (3 digits)
        int a;
        switch (cardTypeIndex)
        {
        case 0:
            a = 1111;
            break;
        case 1:
            a = 2222;
            break;
        case 2:
            a = 3333;
            break;
        case 3:
            a = 4444;
            break;
        default:
            a = 1234; // just a random value
            break;
        }
        snprintf(bankcard.cvv, sizeof(bankcard.cvv), "%03d", rand() % 1000);

        // Generate the full card number using the account ID and random digits
        snprintf(bankcard.cardNumber, sizeof(bankcard.cardNumber), "%d%lld%lld%02d", a, account.accountID, account.ownerID, rand() % 100);

        // The balance of a new Bank card is 0.00.
        bankcard.cardbalance = 0.00;        

        // Set card as not blocked (default is unblocked)
        bankcard.cardBlocked = 0;

        // Prompt for a PIN for the card
        setAndConfirmPIN(bankcard.PIN);
     
        bankcard.cardaccountID = account.accountID;

        // Inform the client that the card request is successful
        printf(GREEN "Your card request has been successfully submitted.\n" RESET "You can collect it at the bank once approved.\n");
        saveBankCardToFile(&bankcard);
    }
    else if (strcmp(response, "n") == 0)
    {
        printf(ORANGE "You have declined the bank card request.\n" RESET);
    }
    else
    {
        printf(RED "Invalid response. Please answer 'y' or 'n'.\n" RESET);
    }
}
