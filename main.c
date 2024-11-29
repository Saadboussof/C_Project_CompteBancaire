#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tools.h"
#include "client.h"
#include "account.h"

void main();

void main()
{
    srand(time(NULL)); // Seed the random number generator
    printf("Welcome to your BANK MANAGMENT SYSTEM\n");

    char *Choices[] = {
        "Client Portal",
        "Manager Dashboard",
        "Employee Dashboard",
        "Exit",
        NULL};

    int choice = choose_item(Choices, "Make your choice");

    switch (choice)
    {
    case 0:
        Client_Portal();
        break;
    case 1:
        printf("Manager Dashboard");
        break;
    case 2:
        printf("Employee Dashboard");
        break;
    default:
        exit(0);
        break;
    }
}
