#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining a structure for the bank account
typedef struct {
    int account_number;
    char owner_name[100];
    float balance;
} BankAccount;

// Function to create a new bank account
void create_account(BankAccount *account) {
    printf("Enter account number: ");
    scanf("%d", &account->account_number);
    printf("Enter account holder's name: ");
    scanf("%s", account->owner_name);
    account->balance = 0.0;
    printf("Account created successfully!\n");
}

// Function to deposit money
void deposit(BankAccount *account) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    account->balance += amount;
    printf("Deposited %.2f successfully!\n", amount);
}

// Function to withdraw money
void withdraw(BankAccount *account) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (account->balance >= amount) {
        account->balance -= amount;
        printf("Withdrew %.2f successfully!\n", amount);
    } else {
        printf("Insufficient balance!\n");
    }
}

// Function to check account balance and details
void check_balance(BankAccount *account) {
    printf("Account Number: %d\n", account->account_number);
    printf("Account Holder: %s\n", account->owner_name);
    printf("Balance: %.2f\n", account->balance);
}

// Function to save account details to a file
void save_account(BankAccount *account, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(account, sizeof(BankAccount), 1, file);
    fclose(file);
    printf("Account saved successfully!\n");
}

// Function to load account details from a file
void load_accounts(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No accounts found.\n");
        return;
    }
    
    BankAccount account;
    printf("\nLoaded accounts:\n");
    while (fread(&account, sizeof(BankAccount), 1, file)) {
        printf("\nAccount Number: %d\n", account.account_number);
        printf("Account Holder: %s\n", account.owner_name);
        printf("Balance: %.2f\n", account.balance);
    }
    fclose(file);
}

int main() {
    BankAccount account;
    int choice;
    const char *filename = "accounts.dat";
    
    while (1) {
        printf("\n---- Bank Account Management ----\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Save Account\n");
        printf("6. Load All Accounts\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                create_account(&account);
                break;
            case 2:
                deposit(&account);
                break;
            case 3:
                withdraw(&account);
                break;
            case 4:
                check_balance(&account);
                break;
            case 5:
                save_account(&account, filename);
                break;
            case 6:
                load_accounts(filename);
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid option, try again.\n");
        }
    }
    
    return 0;
}
