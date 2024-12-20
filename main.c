<<<<<<< HEAD
#include "tools.h"
#include "client.h"
#include "account.h"
#include "employee.h"

void welcom()
{
    getch();

    displaySpectacularLoadingBar(50);
    
    for (int i = 0; i <= 6; i++)
    {
        fordelay(100000000);
    }

    system("cls");
    
    printf(CYAN "\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome to your BANK MANAGMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n" RESET);
}

int pmb = 1;

void main()
{
    srand(time(NULL)); // Seed the random number generator
    
    system("cls"); // Clear the screen

    if (pmb) welcom();
    pmb = 0;
    
    char *Choices[] = {
        "Client Portal",
        "Employee Dashboard",
        "Exit",
        NULL};

    int choice = choose_item(Choices, "** HOME **");

    while(1) {
        switch (choice)
        {
            case 0:
                Client_Portal();
                break;
            case 1:
                Employee_Portal();
                break;
            default:
                printf(RED "Exiting program.\n" RESET);
                exit(0);
                break;
        }
    }
    
}
=======
<<<<<<< HEAD
#include "tools.h"
#include "client.h"
#include "account.h"
#include "employee.h"

void welcom()
{
    getch();

    displaySpectacularLoadingBar(50);
    
    for (int i = 0; i <= 6; i++)
    {
        fordelay(100000000);
    }

    system("cls");
    
    printf(CYAN "\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome to your BANK MANAGMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n" RESET);
}

int pmb = 1;

void main()
{
    srand(time(NULL)); // Seed the random number generator
    
    system("cls"); // Clear the screen

    if (pmb) welcom();
    pmb = 0;
    
    char *Choices[] = {
        "Client Portal",
        "Employee Dashboard",
        "Exit",
        NULL};

    int choice = choose_item(Choices, "** HOME **");

    while(1) {
        switch (choice)
        {
            case 0:
                Client_Portal();
                break;
            case 1:
                Employee_Portal();
                break;
            default:
                printf(RED "Exiting program.\n" RESET);
                exit(0);
                break;
        }
    }
    
}
=======
#include "tools.h"
#include "client.h"
#include "account.h"
#include "employee.h"

void welcom()
{
    getch();

    displaySpectacularLoadingBar(50);
    
    for (int i = 0; i <= 6; i++)
    {
        fordelay(100000000);
    }

    system("cls");
    
    printf(CYAN "\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome to your BANK MANAGMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n" RESET);
}

int pmb = 1;

void main()
{
    srand(time(NULL)); // Seed the random number generator
    
    system("cls"); // Clear the screen

    if (pmb) welcom();
    pmb = 0;
    
    char *Choices[] = {
        "Client Portal",
        "Employee Dashboard",
        "Exit",
        NULL};

    int choice = choose_item(Choices, "** HOME **");

    while(1) {
        switch (choice)
        {
            case 0:
                Client_Portal();
                break;
            case 1:
                Employee_Portal();
                break;
            default:
                printf(RED "Exiting program.\n" RESET);
                exit(0);
                break;
        }
    }
    
}
>>>>>>> 6f8d7a289cf5dc1a39039cabbb1878fda90a55ea
>>>>>>> 8adf12a3f10be7a99795a77e01ef902d2b24e190
