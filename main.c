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

    printf("-----Welcome to your BANK MANAGMENT SYSTEM------\n");
    
    int choice;
    char *Choices[] = {
        "Log in",
        "Sign up",
        "Exit",
        NULL};

    choice = choose_item(Choices, "Make your choice");

    if (choice == 0)
    {
        printf("Log in");
    }
    else if (choice == 1)
    {
        printf("Sign up");
    }
    else if (choice == 2)
    {
        printf("Exit");
    }

    return 0;
}
