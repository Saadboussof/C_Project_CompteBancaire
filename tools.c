#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // For _getch()
#include <time.h>

#define ACCOUNT_NUMBER_MIN 0
#define ACCOUNT_NUMBER_MAX 9999999999

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

// Define ANSI color codes for highlighting and style
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"

int choose_item(char **items, char *title) {
    int selected_option = 0;
    int key;

    // Count items in the list
    int item_count = 0;
    while (items[item_count] != NULL) {
        item_count++;
    }

    while (1) {

        printf(BOLD YELLOW "%s:\n" RESET, title);

        // Display menu options with highlighting
        for (int i = 0; i < item_count; i++) {
            if (i == selected_option) {
                printf(GREEN "> %s\n" RESET, items[i]);
            } else {
                printf(WHITE "  %s\n" RESET, items[i]);
            }
        }

        // Get user input for navigation
        key = _getch();
        if (key == 224) {  // Arrow key prefix (but we don't yet know which one)
            key = _getch();
            if (key == 72 && selected_option > 0) {  // Up arrow
                selected_option--;
            } else if (key == 80 && selected_option < item_count - 1) {  // Down arrow
                selected_option++;
            }
        } else if (key == 13) {  // Enter key
            return selected_option;
        }
        system("cls");
    }
}
