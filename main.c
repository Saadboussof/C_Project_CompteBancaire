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

    printf("Welcome to your BANK MANAGMENT SYSTEM\n");

    int choice;
    char *Choices[] = {
        "Log in",
        "Sign up",
        "Exit"};

    choice = choose_item(Choices, "Make your choice");

    if (choice == 1)
    {
        // signUp();
        printf("Sign up");
    }
    else if (choice == 2)
    {
        // logIn();
        printf("Log in");
    }
    else
    {
        printf("Exit");
    }

    return 0;
}
