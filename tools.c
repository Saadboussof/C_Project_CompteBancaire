#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h> // For _getch()
#include <time.h>
#include <unistd.h> // For usleep()
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

// Function to print the menu with advanced style
int choose_item(char **items, char *title)
{
    int selected_option = 0;
    int key;

    // Count items in the list until NULL value
    int item_count = 0;
    while (items[item_count] != NULL)
    {
        item_count++;
    }

    while (1)
    {
        // Print title in bold and underlined yellow
        printf(BOLD UNDERLINE YELLOW "%s:\n" RESET, title);

        // Display menu options with highlighting on new lines
        for (int i = 0; i < item_count; i++)
        {
            if (i == selected_option)
            {
                // Highlight selected option with green, red for "Exit" or "Return"
                if (strcmp(items[i], "Exit") == 0 || strcmp(items[i], "Return") == 0)
                {
                    printf(RED "  > %s " RESET, items[i]);  // Red for Exit/Return
                }
                else
                {
                    printf(GREEN "  > %s " RESET, items[i]);  // Green for selected options
                }
            }
            else
            {
                // Non-selected options in white, red for Exit/Return
                if (strcmp(items[i], "Exit") == 0 || strcmp(items[i], "Return") == 0)
                {
                    printf(RED "    %s " RESET, items[i]);  // Red for Exit/Return
                }
                else
                {
                    printf(WHITE "    %s " RESET, items[i]);  // White for normal options
                }
            }
            printf("\n");  // Move to the next line after each option
        }

        // Get user input for navigation
        key = _getch();
        if (key == 224)
        { // Arrow key prefix
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
            PIN_hide(PIN, sizeof(tempPIN));
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

// Function to check if a string contains only letters and spaces
int isAlphaString(char *str) {
    while (*str) {
        if (!isalpha(*str) && *str != ' ') { // Allow only letters and spaces
            return 0; // Invalid
        }
        str++;
    }
    return 1; // Valid
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

void fordelay(int j)
{
  int i, k;
  for (i = 0; i < j; i++)
    k = i;
}

void displaySpectacularLoadingBar(int duration) 
{
    const int barWidth = 40; // Width of the progress bar
    char spinner[] = "|/-\\"; // Spinner animation
    int spinnerIndex = 0;     // Index for spinner animation

    printf("\n\n");
    printf(CYAN "Starting the application... Please wait.\n\n" RESET);

    // Loading bar
    for (int progress = 0; progress <= 100; progress++) {
        int pos = (progress * barWidth) / 100; // Calculate current position in the bar

        // Color gradient based on progress
        const char *color;
        if (progress < 25)
            color = RED;
        else if (progress < 50)
            color = YELLOW;
        else if (progress < 75)
            color = GREEN;
        else
            color = CYAN;

        // Dynamic loading message
        const char *message;
        if (progress < 25)
            message = "Initializing...";
        else if (progress < 50)
            message = "Loading Modules...";
        else if (progress < 75)
            message = "Almost Ready...";
        else
            message = "Finalizing...";

        // Clear the current line and print the loading bar
        printf("\r%s[", color);
        for (int i = 0; i < barWidth; i++) {
            if (i < pos) {
                printf("#"); // Filled blocks
            } else {
                printf(" "); // Empty space
            }
        }
        printf("] %d%% %c %s" RESET, progress, spinner[spinnerIndex], message);

        // Update the spinner animation
        spinnerIndex = (spinnerIndex + 1) % 4;

        fflush(stdout); // Force immediate output

        // Delay to simulate loading
        usleep(duration * 1000);
    }

    printf("\n\n");
    printf(GREEN "Application loaded successfully! Enjoy your experience. \n" RESET);
    printf("\n\n");
}

// Gradient color array
const char *colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};

void gradientSpinner(int duration) {
    char spinner[] = "|/-\\";
    int spinnerIndex = 0;

    printf("\nAccessing Account...\n");

    for (int i = 0; i < 100; i++) {
        printf("\r%s%c " RESET "Loading... %d%%", colors[i % 6], spinner[spinnerIndex], i + 1);

        fflush(stdout);
        spinnerIndex = (spinnerIndex + 1) % 4;
        usleep(duration * 1000); // Adjust speed
    }

    printf("\nDone!\n");
}

void typingEffect(const char *text, int speed) {
    for (int i = 0; i < strlen(text); i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(speed * 1000);
    }
    printf("\n");
}


