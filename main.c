#include "tools.h"
#include "client.h"
#include "account.h"

void main()
{
    srand(time(NULL)); // Seed the random number generator
    printf(CYAN "Welcome to your BANK MANAGMENT SYSTEM\n" RESET);

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
