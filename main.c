#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "user.h"

int main() {
    User user;
    Account acc;
    int choice;

    while (1) {
        printf("\n 1. Sign Up \n 2. Log In \n 3. Exit \n");
        printf("  Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp(&user);
                break;
            case 2:
                if (logIn(&user)) {
                    int accountNumber;
                    printf(" Enter account number : ");
                    scanf("%d", &accountNumber);
                    createAccount(&acc, accountNumber);
                    displayAccount(&acc);
                }
                break;
            case 3:
                exit(0);
            default:
                printf("invalid azerty ! Please try again.\n");
        }
    }

    return 0;
}
