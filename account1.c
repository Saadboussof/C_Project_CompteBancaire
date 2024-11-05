#include <stdio.h>
#include "account.h"

void createAccount(Account *acc, int accountNumber) {
    acc->accountNumber = accountNumber;
    acc->balance = 0.0; 
    FILE *file ;
    file = fopen("managingaccounts.txt","w+");
    if ( file == NULL ){
        printf(" failed :'( ");
    }
    fprintf(file," acc num %d balance %.2f \n",acc->accountNumber,acc->balance);
    fclose(file);
}
void displayAccount() {
    FILE *file ;
    file = fopen("managingaccounts.txt","r");
    if ( file == NULL ){
        printf(" failed :'( ");
    }
    double bal ;
    int accnum ;
    fscanf(file," the accountnum : %d \n balance : %.2f \n",accnum , bal);
    printf("Account Number: %d \n", accnum);
    printf("Balance: %.2f \n",bal);
    fclose(file);
}
