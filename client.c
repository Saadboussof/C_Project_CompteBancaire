#include <stdio.h>
#include <string.h>
#include "client.h"
#include "tools.h"
#include "file_operations.h"
#include "account.h"

char CIN[9] = {
    '\0',
};

void logIn_Client()
{

    if (!strcmp(CIN, "\0"))
    {
        printf("Enter CIN to log in please: ");
        scanf(" %8[^\n]s", CIN);
    }
    // Find the client using CIN
    Client *client = findClientByCIN(CIN);
    if (client == NULL)
    {
        printf("Client with CIN %s not found.\n", CIN);
        signUp();
    }

    char password[10];
    while(1){
        printf("Enter your password: ");
        scanf(" %9[^\n]s", password);


        if (strcmp(client->password, password) == 0)
        {
            printf("log in Client successful! Welcome, %s.\n", client->name);
            logIn_Account(client->clientID);
        }
        else
        {
            printf("Incorrect password. Please try again.\n"); // check password
        }
    }
}

void signUp()
{
    if (!strcmp(CIN, "\0"))
    {
        printf("Enter CIN for new client: ");
        scanf(" %8[^\n]s", CIN);
    }

    // Check if client already exists
    if (findClientByCIN(CIN) != NULL)
    {
        printf("Client with CIN %s already exists.\n", CIN);
        logIn_Client();
    }

    createClient();
}

void createClient()
{
    Client newClient;

    printf("Creating a new Client...\n");

    printf("Enter Client Name: ");
    scanf(" %[^\n]s", newClient.name);

    strncpy(newClient.CIN, CIN, sizeof(newClient.CIN) - 1);
    newClient.CIN[sizeof(newClient.CIN) - 1] = '\0';

    printf("Enter Client Phone Number: ");
    scanf(" %[^\n]s", newClient.phoneNumber);

    printf("Enter Client Address: ");
    scanf(" %[^\n]s", newClient.address);

    newClient.isBlacklisted = 0;

    printf("Set a strong password: ");
    scanf(" %9[^\n]s", newClient.password);

    newClient.clientID = generateRandomAccountNumber();
    printf("Your Client ID: %lld\n", newClient.clientID);

    getCurrentDate(newClient.dateCreated, sizeof(newClient.dateCreated));
    printf("Client Created on: %s\n", newClient.dateCreated);

    saveClientToFile(&newClient);
    logIn_Client();
}
