#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"
#include "tools.h"
#include "file_operations.h"
#include "account.h"

#define attemptCount_LIMIT 3
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

char CIN[9] = {'\0'};

void logIn_Client();
void signUp();
Client *findClientByCIN(char *CIN);
void authenticateClient(Client *client);
void requestCIN();
void createClient();
void saveClientToFile(Client *client);
void displayClientDetails(Client *client);

void logIn_Client()
{
    // Request CIN if it's not already provided
    if (strcmp(CIN, "\0") == 0)
    {
        requestCIN();
    }

    // Attempt to find client by CIN
    Client *client = findClientByCIN(CIN);
    while (client == NULL)
    {
        printf("Client with CIN: %s not found.\n", CIN);
        printf("1 - Retry CIN\n2 - Sign up as new client\n");

        int choice;
        scanf("%1d", &choice);

        // while the CIN still incorrect, the client didn't want to sign up, or he write an invalide choice: he still in the loop
        switch (choice)
        {
        case 1:
            requestCIN();
            client = findClientByCIN(CIN);
            break;
        case 2:
            signUp();
            client = findClientByCIN(CIN);
            break;
        default:
            printf("Invalid choice. Please enter 1 or 2.\n");
            break;
        }
    }

    authenticateClient(client);
}

void requestCIN()
{
    printf("Enter your CIN: ");
    scanf(" %8s", CIN);
}

void authenticateClient(Client *client)
{
    char PIN[5];
    int attemptCount = 0;

    while (attemptCount < attemptCount_LIMIT)
    {
        printf("Enter your PIN: ");
        PIN_hide(PIN, sizeof(PIN));

        if (validatePIN(client->PIN, PIN))
        {
            printf(CYAN"\nWelcome, %s! Accessing BANK MANAGEMENT SYSTEM...\n"RESET, client->name);
            displayClientDetails(client);
            logIn_Account(client->clientID);
            return;
        }
        else
        {
            printf("Incorrect PIN. Please try again.\n");
            attemptCount++;
        }
    }
    printf("Too many failed attempts. Exiting...\n"); // Just a simple message still no procedures
}

void signUp()
{
    if (strcmp(CIN, "\0") == 0)
    {
        requestCIN();
    }

    if (findClientByCIN(CIN) != NULL)
    {
        printf("Client with CIN %s already exists. Redirecting to login...\n", CIN);
        logIn_Client();
    }
    else
    {
        createClient();
    }
}

void createClient()
{
    Client newClient;

    printf("Creating a new client...\n");

    printf("Enter Client Name: ");
    scanf(" %[^\n]", newClient.name);

    strncpy(newClient.CIN, CIN, sizeof(newClient.CIN) - 1);
    newClient.CIN[sizeof(newClient.CIN) - 1] = '\0';

    printf("Enter Client Phone Number: ");
    scanf(" %[^\n]", newClient.phoneNumber);

    printf("Enter Client Address: ");
    scanf(" %[^\n]", newClient.address);

    newClient.isBlacklisted = 0;

    printf("Set a PIN: ");
    PIN_hide(newClient.PIN, sizeof(newClient.PIN));

    // Generate unique client ID and creation date
    newClient.clientID = generateRandomAccountNumber();
    printf("Your Client ID: %lld\n", newClient.clientID);

    getCurrentDate(newClient.dateCreated, sizeof(newClient.dateCreated));
    printf("Client created on: %s\n", newClient.dateCreated);

    // Save new client to file and redirect to login
    saveClientToFile(&newClient);
    printf("Sign-up successful. Redirecting to login...\n");
    logIn_Client();
}

Client *findClientByCIN(char *CIN)
{
    FILE *file = fopen("clients.dat", "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    Client *client = malloc(sizeof(Client));
    if (client == NULL)
    {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    while (fread(client, sizeof(Client), 1, file) == 1)
    {
        if (strcmp(client->CIN, CIN) == 0)
        {
            fclose(file);
            return client;
        }
    }

    free(client);
    fclose(file);
    return NULL;
}


void saveClientToFile(Client *client)
{
    FILE *file = fopen("clients.dat", "ab");
    if (file == NULL)
    {
        printf("Failed to open file for saving client.\n");
    }

    fwrite(client, sizeof(Client), 1, file);
    fclose(file);
    printf("Client saved successfully!\n");
}

void displayClientDetails(Client *client) {
    if (client == NULL) {
        printf("Client data is unavailable.\n");
        return;
    }

    printf("Client ID         : %lld\n", client->clientID);
    printf("CIN               : %s\n", client->CIN);
    printf("Name              : %s\n", client->name);
    printf("Phone Number      : %s\n", client->phoneNumber);
    printf("Address           : %s\n", client->address);
    printf("PIN               : ****\n");  // Display asterisks for security reasons
    printf("Blacklisted       : %s\n", client->isBlacklisted ? "Yes" : "No");
    printf("Account Created on: %s\n", client->dateCreated);
}