#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h> // For _getch()
#include <time.h>
#include "tools.h"

// Define the limites for generateRandomAccountNumber
#define ACCOUNT_NUMBER_MIN 10000
#define ACCOUNT_NUMBER_MAX 99999

long long generateRandomAccountNumber()
{
    return ACCOUNT_NUMBER_MIN + (rand() % (ACCOUNT_NUMBER_MAX + 1 - ACCOUNT_NUMBER_MIN));
}

void getCurrentDate(char *buffer, size_t bufferSize)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, bufferSize, "%Y-%m-%d at %H:%M:%S", t);
}

int choose_item(char **items, char *title)
{
    int selected_option = 0;
    int key;

    // Count items in the list until NULL value that ~SHOULD~ be mentionned at the end of each list
    int item_count = 0;
    while (items[item_count] != NULL)
    {
        item_count++;
    }

    while (1)
    {

        printf(BOLD YELLOW "%s:\n" RESET, title);

        // Display menu options with highlighting
        for (int i = 0; i < item_count; i++)
        {
            if (i == selected_option)
            {
                printf(GREEN "> %s\n" RESET, items[i]);
            }
            else
            {
                printf(WHITE "  %s\n" RESET, items[i]);
            }
        }

        // Get user input for navigation
        key = _getch();
        if (key == 224)
        { // Arrow key prefix (but we still don't yet know which one (up/down))
            key = _getch();
            if (key == 72 && selected_option > 0)
            { // Up arrow
                selected_option--;
            }
            else if (key == 80 && selected_option < item_count - 1)
            { // Down arrow
                selected_option++;
            }
        }
        else if (key == 13)
        { // Enter key
            return selected_option;
        }
        system("cls");
    }
}

bool setAndConfirmPIN(char *PIN) {
    char tempPIN[5] = "\0";
    bool check = false;

    while (1) {
        // Step 1: Set the PIN
        while (!check) {
            printf("Set a 4-digit PIN: ");
            PIN_hide(PIN, sizeof(PIN));
            check = (strlen(PIN) == 4) && isNumericString(PIN);
            if (!check) {
                printf("Invalid PIN. Please ensure it is a 4-digit number.\n");
            }
        }
        check = false;

        // Step 2: Confirm the PIN
        printf("Confirm your PIN: ");
        PIN_hide(tempPIN, sizeof(tempPIN));

        if (!validatePIN(PIN, tempPIN)) {
            printf("PINs do not match. Try again.\n");
        } else {
            return true; // PIN successfully set
        }
    }
}

void PIN_hide(char *PIN, int max_length)
{
    int i = 0;
    char ch;

    while (i < max_length - 1 && (ch = _getch()) != '\r')  // '\r' is Enter key in Windows
    { 
        if (ch == '\b' && i > 0)  // Handle backspace
        { 
            i--;
            printf("\b \b");  // Move back, overwrite with space, and move back again
        }
        else if (ch != '\b')
        {
            PIN[i++] = ch;
            printf("*");
        }
    }
    PIN[i] = '\0'; // Null-terminate the PIN string
    printf("\n");
}

int validatePIN(const char *enteredPIN, const char *correctPIN)
{
    return strcmp(enteredPIN, correctPIN) == 0;
}

// Function to check if a string contains only alphabetic characters
int isAlphaString(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i])) // If any character is not alphabetic, return 0
            return 0;
    }
    return 1; // All characters are alphabetic
}

// Function to check if a string contains only numeric characters
int isNumericString(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i])) // If any character is not numeric, return 0
            return 0;
    }
    return 1; // All characters are numeric
}

// Function to check if a string contains only alphanumeric characters
int isAlphanumericString(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalnum(str[i])) // If any character is not alphanumeric, return 0
            return 0;
    }
    return 1; // All characters are alphanumeric
}