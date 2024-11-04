#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "tools.h"
#include "client.h"
#include "account.h"
#include "file_operations.h"

int main()
{
    srand(time(NULL)); // Seed the random number generator

    printf("Welcome to your BANK MANAGMENT SYSTEM");

    int choice;

    printf("1. Sign Up\n");
    printf("2. Log In\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        signUp();
    }
    else if (choice == 2)
    {
        logIn();
    }
    else
    {
        printf("Invalid option.\n");
    }

    return 0;
}
