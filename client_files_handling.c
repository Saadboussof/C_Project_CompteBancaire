#include "client.h"
#include <errno.h>

int saveClientToFile(Client *client)
{
    FILE *file = fopen("clients.dat", "ab");
    if (file == NULL)
    {
        printf(RED "ERROR : Failed to open file for saving client.\n" RESET);
        printf(RED "A critical error occurred while processing your request.\n" BOLD "Please try again later or contact support.\n" RESET);
        return 0;
    }

    fwrite(client, sizeof(Client), 1, file);
    fclose(file);
    return 1;
}

// Function to search for a client by CIN or clientID
Client *findClient(char *CIN, long long clientID, int searchByCIN) // 0- ID   1- CIN
{
    FILE *file = fopen("clients.dat", "ab+");

    if (file == NULL)
    {
        printf(RED "ERROR : Failed to open file clients file\n" RESET);
        printf(RED "We're sorry, but we encountered a technical issue while accessing client data.\n" BOLD "Please try again later or contact support.\n" RESET);
        return NULL;
    }

    Client *client = malloc(sizeof(Client));
    if (client == NULL)
    {
        printf(RED "ERROR : Failed to allocate memory\n" RESET);
        printf(RED "A critical error occurred while processing your request.\n" BOLD "Please try again later or contact support.\n" RESET);
        fclose(file);
        return NULL;
    }

    while (fread(client, sizeof(Client), 1, file) == 1)
    {
        // Search by CIN if searchByCIN is true
        if (searchByCIN && strcmp(client->CIN, CIN) == 0)
        {
            fclose(file);
            return client; // Return client if CIN matches
        }
        // Search by clientID if searchByCIN is false
        else if (!searchByCIN && client->clientID == clientID)
        {
            fclose(file);
            return client; // Return client if clientID matches
        }
    }

    free(client); // Free allocated memory if no match is found
    fclose(file);
    return NULL; // Return NULL if neither CIN nor clientID is found
}

void processClientRequest()
{
    FILE *requestFile = fopen("clients.dat", "rb+"); // Open for both read and write
    if (requestFile == NULL)
    {
        printf(RED "ERROR : Failed to open clients file" RESET);
        printf(RED "Unable to access the client database.\n" BOLD "Please report this issue to the technical team for resolution.\n" RESET);
        return;
    }

    FILE *tempFile = fopen("temp_requests.dat", "wb"); // Temporary file to store modified clients
    if (tempFile == NULL)
    {
        printf(RED "ERROR : Failed to open temporary file.\n" RESET);
        printf(RED "A critical error occurred while processing your request. Please report this issue to the technical team for resolution.\n" RESET);
        fclose(requestFile);
        return;
    }

    Client client;
    int hasRequests = 0;

    while (fread(&client, sizeof(Client), 1, requestFile) == 1)
    {
        if (client.activation == 0)
        {
            hasRequests++;
            // Only ask questions for inactive clients
            printf("======" BLUE " Reviewing Request N " RESET BOLD ORANGE "%d" RESET " for Client : " RESET "=====\n" RESET);
            displayClientDetails(&client);

            // Ask three questions: delete, activate, or skip
            printf(PURPLE "What would you like to do?\n" RESET);
            printf(YELLOW "0-" RESET " Skip this client\n");
            printf(GREEN "1-" RESET " Activate this client\n");
            printf(RED "2-" RESET " Delete this client\n");
            printf(PURPLE "Enter your choice: " RESET);

            char choice;
            choice = getch();
            printf("\n");

            if (choice == '1')
            {
                // Employee chose to activate the client, so set their account to active
                client.activation = 1;
                fwrite(&client, sizeof(Client), 1, tempFile); // Save the updated client to the temporary file
                printf(GREEN "Client with CIN : %s activated successfully.\n" RESET, client.CIN);
            }
            else if (choice == '2')
            {
                // Employee chose to delete the client, so don't save them back to the file
                printf(RED "Client request with CIN : %s rejected and deleted.\n" RESET, client.CIN);
                continue; // Skip writing this client to the temp file (its just written for clarifcation)
            }
            else
            {
                // Invalid choice, skip the client
                printf(YELLOW "Client request with CIN : %s skipped.\n" RESET, client.CIN);
                fwrite(&client, sizeof(Client), 1, tempFile); // Save unchanged client to the temporary file
            }
        }
        else
        {
            // For active clients, we just copy them to the temp file unchanged
            fwrite(&client, sizeof(Client), 1, tempFile); // Copy active client as-is to the temp file
        }
    }

    fclose(requestFile);
    fclose(tempFile);

    if (!hasRequests)
    {
        printf(ORANGE "\tNo client requests found.\n" RESET);
        remove("temp_requests.dat");
        return;
    }

    // Replace old client file with updated one (with modified activation status)
    remove("clients.dat");                      // Delete the original file
    rename("temp_requests.dat", "clients.dat"); // Rename the temporary file to the original file name

    printf(BLUE "\tProcessed " RESET BOLD "%d" RESET BLUE " client requests.\n" RESET);
}
