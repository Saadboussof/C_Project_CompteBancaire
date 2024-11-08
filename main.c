#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tools.h"
#include "client.h"
#include "account.h"
#include "file_operations.h"



int main()
{
    srand(time(NULL)); // Seed the random number generator
    printf("Welcome to your BANK MANAGMENT SYSTEM\n");

    char *Choices[] = {
        "Log in",
        "Sign up",
        "Exit",
        NULL};

    int choice = choose_item(Choices, "Make your choice");
    if (choice == 0)
    {
        logIn_Client();
    }
    else if (choice == 1)
    {
        signUp();
    }
    else
    {
        exit(0);
    }

    // displayAllAccounts();
    return 0;
}
