#include "client.h"

void displayClientDetails(Client *client)
{
    printf(PURPLE "---------- Client information : ----------\n" RESET);
    printf("Client ID         : %lld\n", client->clientID);
    printf("CIN               : %s\n", client->CIN);
    printf("Name              : %s\n", client->name);
    printf("Phone Number      : %s\n", client->phoneNumber);
    printf("Address           : %s\n", client->address);
    printf("Account Created on: %s\n", client->dateCreated);
    printf(PURPLE "------------------------------------------\n" RESET);
}

void displayAllClients()
{
    FILE *file = fopen("clients.dat", "rb");
    if (file == NULL)
    {
        perror(RED "ERROR : Failed to open clients file" RESET);
        printf(RED "Unable to access the client database. Please report this issue to the technical team for resolution.\n" RESET);
        return; // Exit the function gracefully
    }

    Client client;
    int count = 0;

    printf(PURPLE 
    "\n------------------------------------------- All Clients -------------------------------------------\n" RESET);

    printf("| %-3s | %-6s | %-10s | %-30s | %-11s | %-12s | %-7s | %-25s |\n",
           "No", "Client ID", "CIN", "Name", "Phone Number", "Blacklisted", "Active", "Date Created");

    printf(PURPLE "----------------------------------------------------------------------------------------------------\n" RESET);

    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        count++;
        printf("| %-3d | %-6lld | %-10s | %-30s | %-11s | %-12s | %-7s | %-25s |\n",
                count,
                client.clientID,
                client.CIN,
                client.name,
                client.phoneNumber,
                client.Blacklisted ? RED "Yes" RESET : GREEN "No" RESET,
                client.activation ? "No" : ORANGE "Yes" RESET,
                client.dateCreated);
    }

    fclose(file);

    if (count == 0)     // file opened but no clients found
    {
        printf(ORANGE "No clients found in the database.\nIf you think maybe there is an issue please do not hesitate to report it to the technical team for resolution.\n" RESET);
    }
    
    else
    {
        printf(GREEN "\nDisplayed %d client(s) successfully.\n" RESET, count);
    }
}

void displayFilteredClients(int filterType, int filterValue)    // 0- Blacklist  1- Activation 
{
    FILE *file = fopen("clients.dat", "rb");
    if (file == NULL)
    {
        perror(RED "ERROR : Failed to open clients file" RESET);
        printf(RED "Unable to access the client database. Please report this issue to the technical team for resolution.\n" RESET);
        return;
    }

    Client client;
    int count = 0;

    // Determine the filter description based on filterType
    char *filterTypeDescription = filterType ?  "Activation" : "Blacklist" ;
    char *filterValueDescription = filterType ? 
    (filterValue ? GREEN "Active" RESET: ORANGE "Inactive" RESET) : (filterValue ? RED "Blacklisted" RESET : GREEN "Not-Blacklisted" RESET) ;

    printf(PURPLE "\n-------------------- Filtered Clients (%s: %s) --------------------\n" RESET,
           filterTypeDescription, filterValueDescription);
    printf("| %-3s | %-6s | %-10s | %-30s | %-11s | %-25s |\n",
           "No", "Client ID", "CIN", "Name", "Phone Number", "Date Created");
    printf(PURPLE "-----------------------------------------------------------------------\n" RESET);

    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        // Check based on filterType
        int match = filterType ? (client.activation == filterValue) : (client.Blacklisted == filterValue);
        
        if (match)
        {
            count++;
            printf("| %-3d | %-6lld | %-10s | %-30s | %-11s | %-25s |\n",
                   count,
                   client.clientID,
                   client.CIN,
                   client.name,
                   client.phoneNumber,
                   client.dateCreated);
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf(ORANGE "No matching clients found.\n" RESET);
    }
    else
    {
        printf(PURPLE "-----------------------------------------------------------------------\n" RESET);
        printf(GREEN "\nDisplayed %d client(s) successfully.\n" RESET, count);
    }
}

