#include "client.h"

// void displayClientDetails(Client *client)
// {
//     setCursor(20, 102);
//     printf(PURPLE "---------- Client information : ----------\n" RESET);
//     setCursor(21, 102);
//     printf("Client ID         : %lld\n", client->clientID);
//     setCursor(22, 102);
//     printf("CIN               : %s\n", client->CIN);
//     setCursor(23, 102);
//     printf("Name              : %s\n", client->name);
//     setCursor(24, 102);
//     printf("Phone Number      : %s\n", client->phoneNumber);
//     setCursor(25, 102);
//     printf("Address           : %s\n", client->address);
//     setCursor(26, 102);
//     printf("Account Created on: %s\n", client->dateCreated);
//     setCursor(27, 102);
//     printf(PURPLE "------------------------------------------\n" RESET);
// }

void displayClientDetails(Client *client)
{
    setCursor(21, 103);
    printf(CYAN "Client ID         :" RESET " %lld\n", client->clientID);
    setCursor(22, 103);
    printf(CYAN "CIN               :" RESET " %s\n", client->CIN);
    setCursor(23, 103);
    printf(CYAN "Name              :" RESET " %s\n", client->name);
    setCursor(24, 103);
    printf(CYAN "Phone Number      :" RESET " %s\n", client->phoneNumber);
    setCursor(25, 103);
    client->dateCreated[10] = '\0';
    printf(CYAN "Account Created on:" RESET " %s\n", client->dateCreated);
    client->dateCreated[10] = ' ';
}

void displayAllClients()
{
    FILE *file = fopen("clients.dat", "rb");
    if (file == NULL)
    {
        printf(RED "ERROR : Failed to open clients file\n" RESET);
        printf(RED "Unable to access the client database.\n" BOLD "Please report this issue to the technical team for resolution.\n" RESET);
        return; // Exit the function gracefully
    }

    Client client;
    int count = 0;
    setCursor(21, 4);

    printf(PURPLE
           "+------------------------------------------------------ All Clients -------------------------------------------------------+\n" RESET);
    setCursor(22, 4);
    printf(PURPLE "|" RESET ORANGE " %-2s " RESET PURPLE "|" RESET ORANGE " %-9s " RESET PURPLE "|" RESET ORANGE " %-8s " RESET PURPLE "|" RESET ORANGE " %-29s " RESET PURPLE "|" RESET ORANGE " %-12s " RESET PURPLE "|" RESET ORANGE " %-11s " RESET PURPLE "|" RESET ORANGE " %-6s " RESET PURPLE "|" RESET ORANGE " %-22s " RESET PURPLE "|" RESET "\n", "No", "Client ID", "CIN", "Name", "Phone Number", "Blacklisted", "Active", "Date Created");
    setCursor(23, 4);
    printf(PURPLE "+--------------------------------------------------------------------------------------------------------------------------+\n" RESET);

    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        count++;
        setCursor(23 + count, 4);
        printf("" PURPLE "|" RESET CYAN " %-2d " RESET PURPLE "|" RESET " %-9lld " PURPLE "|" RESET " %-8s " PURPLE "|" RESET " %-29s " PURPLE "|" RESET BOLD " %-12s " RESET PURPLE "|" RESET " %-11s " PURPLE "|" RESET " %-6s " PURPLE "|" RESET " %-22s " PURPLE "|" RESET "\n",
               count,
               client.clientID,
               client.CIN,
               client.name,
               client.phoneNumber,
               client.Blacklisted ? RED "Yes        " RESET : GREEN "No         " RESET,
               client.activation ? GREEN "Yes   " RESET : RED "No    " RESET,
               client.dateCreated);
    }

    fclose(file);

    if (count == 0) // file opened but no clients found
    {
        printf(ORANGE "No clients found in the database.\nIf you think maybe there is an issue please do not hesitate to report it to the technical team for resolution.\n" RESET);
    }

    else
    {
        setCursor(23 + count, 4);
        printf(PURPLE "+--------------------------------------------------------------------------------------------------------------------------+\n" RESET);
        printf(GREEN "\n\tDisplayed" RESET BOLD " %d " RESET GREEN "client(s) successfully.\n" RESET, count);
    }
}

void displayFilteredClients(int filterType, int filterValue) // 0- Blacklist  1- Activation
{
    FILE *file = fopen("clients.dat", "rb");
    if (file == NULL)
    {
        perror(RED "ERROR : Failed to open clients file" RESET);
        printf(RED "Unable to access the client database.\n" BOLD "Please report this issue to the technical team for resolution.\n" RESET);
        return;
    }

    Client client;
    int count = 0;

    // Determine the filter description based on filterType
    char *filterTypeDescription = filterType ? CYAN "Activation" RESET : CYAN "Blacklist " RESET;
    char *filterValueDescription = filterType ? (filterValue ? GREEN "Active         " RESET : ORANGE "Inactive       " RESET) : (filterValue ? RED "Blacklisted    " RESET : GREEN "Not-Blacklisted" RESET);

    printf(PURPLE "\n+--------- Filtered Clients (%s : %s" PURPLE ") -----------------+\n" RESET,
           filterTypeDescription, filterValueDescription);

    printf(PURPLE "|" RESET ORANGE " %-2s " RESET PURPLE "|" RESET ORANGE " %-9s " RESET PURPLE "|" RESET ORANGE " %-8s " RESET PURPLE "|" RESET ORANGE " %-30s " RESET PURPLE "|" RESET ORANGE " %-12s " RESET PURPLE "|" RESET "\n", "No", "Client ID", "CIN", "Name", "Phone Number");

    printf(PURPLE "+---------------------------------------------------------------------------+\n" RESET);

    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        // // Check based on filterType
        // int match = filterType ? (client.activation == filterValue) : (client.Blacklisted == filterValue);

        if (((filterType && filterValue) && (client.activation == 1)) || ((filterType && !filterValue) && (client.activation == 0)) || ((!filterType && filterValue) && (client.Blacklisted == 1)) || ((!filterType && !filterValue) && (client.Blacklisted == 0)))
        {
            count++;
            printf("" PURPLE "|" RESET CYAN " %-2d " RESET PURPLE "|" RESET " %-9lld " PURPLE "|" RESET " %-8s " PURPLE "|" RESET " %-30s " PURPLE "|" RESET BOLD " %-12s " RESET PURPLE "|" RESET "\n",
                   count,
                   client.clientID,
                   client.CIN,
                   client.name,
                   client.phoneNumber);
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf(PURPLE "|                                                                           |\n" RESET);
        printf(PURPLE "|" RESET ORANGE "                     No matching clients found.                            " RESET PURPLE "|\n" RESET);
        printf(PURPLE "|                                                                           |\n" RESET);
        printf(PURPLE "+---------------------------------------------------------------------------+\n" RESET);
    }
    else
    {
        printf(PURPLE "+---------------------------------------------------------------------------+\n" RESET);
        printf(GREEN "\nDisplayed" RESET BOLD " %d " RESET GREEN "client(s) successfully.\n" RESET, count);
    }
}
