#include "tools.h"
#include "client.h"
#include "account.h"
#include "employee.h"

void welcom()
{
    displaySpectacularLoadingBar(50);

    printf(CYAN "\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome to your BANK MANAGMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n" RESET);
}

void main()
{
    srand(time(NULL)); // Seed the random number generator
<<<<<<< HEAD
    // welcom();
=======

    displayAllClients( 1, 1);
    displaySpectacularLoadingBar(50);
    printf(CYAN "\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome to your BANK MANAGMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n" RESET);
>>>>>>> origin/master

    char *Choices[] = {
        "Client Portal",
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
<<<<<<< HEAD
        printf("Employee Dashboard");
=======
        Employee_Portal();
>>>>>>> origin/master
        break;
    default:
        printf(RED "Exiting program.\n" RESET);
        exit(0);
        break;
    }
}
