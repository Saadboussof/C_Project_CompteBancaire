#include "client.h"
 
void saveClientToFile(Client *client)
{
    FILE *file = fopen("clients.dat", "ab");
    if (file == NULL)
    {
        printf(RED "ERROR : Failed to open file for saving client.\n" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
    }

    fwrite(client, sizeof(Client), 1, file);
    fclose(file);
    printf(GREEN "Client saved successfully!\n" RESET);
}

// Function to search for a client by CIN or clientID
Client *findClient(char *CIN, long long clientID, int searchByCIN)          // 0- ID   1- CIN
{
    FILE *file = fopen("clients.dat", "ab+");
    if (file == NULL)
    {
        printf(RED "ERROR : Failed to open file clients file\n" RESET);
        printf(RED "We're sorry, but we encountered a technical issue while accessing client data. Please try again later or contact support.\n" RESET);
        exit(EXIT_FAILURE); // Exit program if file cannot be opened
    }

    Client *client = malloc(sizeof(Client));
    if (client == NULL)
    {
        printf(RED "ERROR : Failed to allocate memory\n" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
        fclose(file);
        exit(EXIT_FAILURE); // Exit program if memory allocation fails
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

void processClientRequest() {
    FILE *requestFile = fopen("clients.dat", "rb+"); // Open for both read and write
    if (requestFile == NULL) {
        printf(RED "ERROR : Failed to open clients file" RESET);
        printf(RED "Unable to access the client database. Please report this issue to the technical team for resolution.\n" RESET);
        return; // Exit the function gracefully
    }

    FILE *tempFile = fopen("temp_requests.dat", "wb"); // Temporary file to store modified clients
    if (tempFile == NULL) {
        printf(RED "ERROR : Failed to open temporary file.\n" RESET);
        printf(RED "A critical error occurred while processing your request. Please report this issue to the technical team for resolution.\n" RESET);
        fclose(requestFile);
        return;
    }

    Client client;
    int hasRequests = 0;

    while (fread(&client, sizeof(Client), 1, requestFile) == 1) {
        hasRequests = 1;

        if (client.activation == 0) {
            // Only ask questions for inactive clients
            printf(BLUE "Reviewing Request for Client:\n" RESET);
            displayClientDetails(&client);

            // Ask three questions: delete, activate, or skip
            printf(PURPLE "What would you like to do?\n" RESET);
            printf("1 - Activate this client\n");
            printf("2 - Delete this client\n");
            printf(PURPLE "Enter your choice: " RESET);
            
            int choice;
            scanf("%1d", &choice);

            if (choice == 1) {
                // Employee chose to activate the client, so set their account to active
                client.activation = 1;
                fwrite(&client, sizeof(Client), 1, tempFile); // Save the updated client to the temporary file
                printf(GREEN "Client activated successfully.\n" RESET);

            } else if (choice == 2) {
                // Employee chose to delete the client, so don't save them back to the file
                printf(RED "Client request rejected and deleted.\n" RESET);
                continue;  // Skip writing this client to the temp file (its just written for clarifcation)
            } else {
                // Invalid choice, skip the client
                printf(YELLOW "Invalid choice. Skipping this request.\n" RESET);
                fwrite(&client, sizeof(Client), 1, tempFile); // Save unchanged client to the temporary file
            }
        } else {
            // For active clients, we just copy them to the temp file unchanged
            fwrite(&client, sizeof(Client), 1, tempFile); // Copy active client as-is to the temp file
        }
    }

    fclose(requestFile);
    fclose(tempFile);

    if (!hasRequests) {
        printf(BLUE "No client requests found.\n" RESET);
        remove("temp_requests.dat");
        return;
    }

    // Replace old client file with updated one (with modified activation status)
    remove("clients.dat"); // Delete the original file
    rename("temp_requests.dat", "clients.dat"); // Rename the temporary file to the original file name

    printf(BLUE "Processed all client requests.\n" RESET);
}
