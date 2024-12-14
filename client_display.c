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
        printf(RED "ERROR : Failed to open clients file\n" RESET);
        printf(RED "Unable to access the client database. Please report this issue to the technical team for resolution.\n" RESET);
        return; // Exit the function gracefully
    }

    Client client;
    int count = 0;

    printf(PURPLE 
    "\n+------------------------------------------------- All Clients -------------------------------------------------+\n" RESET);

    printf(PURPLE "|" RESET ORANGE " %-1s " RESET PURPLE "|" RESET ORANGE " %-8s " RESET PURPLE "|" RESET ORANGE " %-8s " RESET PURPLE "|" RESET ORANGE " %-15s " RESET PURPLE "|" RESET ORANGE " %-9s " RESET PURPLE "|" RESET ORANGE " %-12s " RESET PURPLE "|" RESET ORANGE " %-8s " RESET PURPLE "|" RESET ORANGE " %-22s " RESET PURPLE "|" RESET "\n", "No", "Client ID", "CIN", "Name", "Phone Number", "Blacklisted", "Active", "Date Created");

    printf(PURPLE "+---------------------------------------------------------------------------------------------------------------+\n" RESET);

    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        count++;
        printf("" PURPLE "|" RESET CYAN " %-2d " RESET PURPLE "|" RESET " %-9lld " PURPLE "|" RESET " %-8s " PURPLE "|" RESET " %-15s " PURPLE "|" RESET BOLD " %-12s " RESET PURPLE "|" RESET " %-21s " PURPLE "|" RESET " %-16s " PURPLE "|" RESET " %-22s " PURPLE "|" RESET "\n",
                count,
                client.clientID,
                client.CIN,
                client.name,
                client.phoneNumber,
                client.Blacklisted ? RED "     Yes     " RESET : GREEN "     No     " RESET,
                client.activation ? RED "   No   " RESET : GREEN "   Yes   " RESET,
                client.dateCreated);
    }

    fclose(file);

    if (count == 0)     // file opened but no clients found
    {
        printf(ORANGE "No clients found in the database.\nIf you think maybe there is an issue please do not hesitate to report it to the technical team for resolution.\n" RESET);
    }
    
    else
    {
        printf(PURPLE "+---------------------------------------------------------------------------------------------------------------+\n" RESET);
        printf(GREEN "\nDisplayed" RESET " %d " GREEN "client(s) successfully.\n" RESET, count);
    }
}

// void displayFilteredClients(int filterType, int filterValue)    // 0- Blacklist  1- Activation 
// {
//     FILE *file = fopen("clients.dat", "rb");
//     if (file == NULL)
//     {
//         perror(RED "ERROR : Failed to open clients file" RESET);
//         printf(RED "Unable to access the client database. Please report this issue to the technical team for resolution.\n" RESET);
//         return;
//     }

//     Client client;
//     int count = 0;

//     // Determine the filter description based on filterType
//     char *filterTypeDescription = filterType ? CYAN "Activation" RESET : CYAN "Blacklist" RESET;
//     char *filterValueDescription = filterType ? 
//     (filterValue ? GREEN "Active" RESET: ORANGE "Inactive" RESET) : (filterValue ? RED "Blacklisted" RESET : GREEN "Not-Blacklisted" RESET) ;

//     printf(PURPLE "\n+--------- Filtered Clients (%s : %s" PURPLE ") -----------+\n" RESET,
//            filterTypeDescription, filterValueDescription);

//     printf(PURPLE "|" RESET ORANGE " %-2s " RESET PURPLE "|" RESET ORANGE " %-9s " RESET PURPLE "|" RESET ORANGE " %-8s " RESET PURPLE "|" RESET ORANGE " %-15s " RESET PURPLE "|" RESET ORANGE " %-10s " RESET PURPLE "|" RESET "\n", "No", "Client ID", "CIN", "Name", "Phone Number");

//     printf(PURPLE "+------------------------------------------------------------+\n" RESET);

//     while (fread(&client, sizeof(Client), 1, file) == 1)
//     {
//         // Check based on filterType
//         int match = filterType ? (client.activation == filterValue) : (client.Blacklisted == filterValue);
        
//         if (match)
//         {
//             count++;
//             printf("" PURPLE "|" RESET CYAN " %-2d " RESET PURPLE "|" RESET " %-9lld " PURPLE "|" RESET " %-8s " PURPLE "|" RESET " %-15s " PURPLE "|" RESET BOLD " %-12s " RESET PURPLE "|" RESET "\n",
//                    count,
//                    client.clientID,
//                    client.CIN,
//                    client.name,
//                    client.phoneNumber);
//         }
//     }

//     fclose(file);

//     if (count == 0)
//     {
//         printf(ORANGE "\t\t\t\t\t\tNo matching clients found.\n" RESET);
//     }
//     else
//     {
//         printf(PURPLE "+------------------------------------------------------------+\n" RESET);
//         printf(GREEN "\nDisplayed" RESET " %d " GREEN "client(s) successfully.\n" RESET, count);
//     }
// }



void displayFilteredClients(int filterType, int filterValue) // 0 - Blacklist, 1 - Activation
{
    FILE *file = fopen("clients.dat", "rb");
    if (file == NULL)
    {
        perror(RED "ERROR: Failed to open clients file" RESET);
        printf(RED "Unable to access the client database. Please report this issue to the technical team for resolution.\n" RESET);
        return;
    }

    Client client;
    int count = 0;

    // Determine the filter descriptions
    char *filterTypeDescription = filterType ? CYAN "Activation" RESET : CYAN "Blacklist" RESET;
    char *filterValueDescription = filterType ? 
        (filterValue ? GREEN "Active" RESET : ORANGE "Inactive" RESET) : 
        (filterValue ? RED "Blacklisted" RESET : GREEN "Not-Blacklisted" RESET);

    // Calculate column widths dynamically
    int maxNameLen = strlen("Name");
    int maxCINLen = strlen("CIN");
    int maxPhoneLen = strlen("Phone Number");

    // First pass: calculate max lengths for fields
    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        if (strlen(client.name) > maxNameLen) maxNameLen = strlen(client.name);
        if (strlen(client.CIN) > maxCINLen) maxCINLen = strlen(client.CIN);
        if (strlen(client.phoneNumber) > maxPhoneLen) maxPhoneLen = strlen(client.phoneNumber);
    }

    // Reset file pointer for second pass
    rewind(file);

    // Dynamic table headers
    printf(PURPLE "\n+------------------ Filtered Clients (%s: %s) ------------------+\n" RESET,
           filterTypeDescription, filterValueDescription);

    printf(PURPLE "|" RESET ORANGE " %-3s " RESET PURPLE "|" RESET ORANGE " %-10s " RESET PURPLE "|" RESET ORANGE " %-*s " RESET PURPLE "|" RESET ORANGE " %-*s " RESET PURPLE "|" RESET ORANGE " %-*s " RESET PURPLE "|\n" RESET,
           "No", "Client ID", maxCINLen, "CIN", maxNameLen, "Name", maxPhoneLen, "Phone Number");

    printf(PURPLE "+-%-3s-+-%-10s-+-%-*s-+-%-*s-+-%-*s-+\n" RESET,
           "---", "----------", maxCINLen, "--------", maxNameLen, "---------------", maxPhoneLen, "-------------");

    // Second pass: display data
    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        int match = filterType ? (client.activation == filterValue) : (client.Blacklisted == filterValue);

        if (match)
        {
            count++;
            printf(PURPLE "|" RESET CYAN " %-3d " RESET PURPLE "|" RESET " %-10lld " PURPLE "|" RESET " %-*s " PURPLE "|" RESET " %-*s " PURPLE "|" RESET " %-*s " RESET PURPLE "|\n" RESET,
                   count, client.clientID, maxCINLen, client.CIN, maxNameLen, client.name, maxPhoneLen, client.phoneNumber);
        }
    }

    fclose(file);

    // Final message
    if (count == 0)
    {
        printf(ORANGE "\tNo matching clients found.\n" RESET);
    }
    else
    {
        printf(PURPLE "+-%-3s-+-%-10s-+-%-*s-+-%-*s-+-%-*s-+\n" RESET,
               "---", "----------", maxCINLen, "--------", maxNameLen, "---------------", maxPhoneLen, "-------------");
        printf(GREEN "\nDisplayed" RESET " %d " GREEN "client(s) successfully.\n" RESET, count);
    }
}
