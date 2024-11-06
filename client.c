#include <stdio.h>
#include <string.h>
#include "client.h"
#include "tools.h"
#include "file_operations.h"

char CIN[9];

// int logIn()
// {
//     printf("Enter CIN to log in: ");
//     scanf(" %8[^\n]s", CIN);

//     // Find the client using CIN
//     Client *client = findClientByCIN(CIN);
//     if (client == NULL)
//     {
//         printf("Client with CIN %s not found.\n", CIN);
//         return -1;
//     }

//     char password[50];
//     printf("Enter password: ");
//     scanf(" %49[^\n]s", password);

//     if (strcmp(client->password, password) == 0)
//     {
//         printf("Login successful! Welcome, %s.\n", client->name);
//         return 0;
//     }
//     else
//     {
//         printf("Incorrect password. Please try again.\n");
//         return -1;
//     }
// }

int signUp()
{
    printf("Enter CIN for new client: ");
    scanf(" %8[^\n]s", CIN);

    // Check if client already exists
    if (findClientByCIN(CIN) != NULL)
    {
        printf("Client with CIN %s already exists. Please log in.\n", CIN);
        return -1;
    }

    if (createClient() == 0)
    {
        printf("Sign-up successful!\n");
        return 0;
    }
    else
    {
        printf("Failed to create client.\n");
        return -1;
    }
}

int createClient()
{
    Client newClient;

    printf("Creating a new Client...\n");

    newClient.clientID = generateRandomAccountNumber();
    printf("Your Client ID: %lld\n", newClient.clientID);

    printf("Enter Client Name: ");
    scanf(" %[^\n]s", newClient.name);

    strncpy(newClient.CIN, CIN, sizeof(newClient.CIN) - 1);
    newClient.CIN[sizeof(newClient.CIN) - 1] = '\0';

    printf("Enter Client Phone Number: ");
    scanf(" %[^\n]s", newClient.phoneNumber);

    printf("Enter Client Address: ");
    scanf(" %[^\n]s", newClient.address);

    newClient.isBlacklisted = 0;

    getCurrentDate(newClient.dateCreated, sizeof(newClient.dateCreated));
    printf("Client Created on: %s\n", newClient.dateCreated);

    if (saveClientToFile(&newClient) == 0)
    {
        printf("Client saved successfully!\n");
        return 0;
    }
    else
    {
        printf("Failed to save client.\n");
        return -1;
    }
}
