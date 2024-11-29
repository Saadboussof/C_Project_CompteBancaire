#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "main.h"
#include "client.h"
#include "account.h"
#include "tools.h"

#define attemptCount_LIMIT 3
#define CYAN "\033[0;36m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define RED "\033[31m"
#define ORANGE "\033[38;5;214m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void Client_Portal();
void logIn_Client();
void signUpRequest();
void requestCIN();
int isValidCIN(char *cin);
void authenticateClient(Client *client);
Client *findClientByCIN(char *CIN);
int checkClientApprovalStatus(Client *client);
void createClient();
void saveRequestToFile(Client *client);
void processClientRequest();
void saveClientToFile(Client *client);
void displayClientDetails(Client *client);
void displayAllClients();

void Client_Portal()
{
    char *Choices[] = {
        "Log in",
        "Sign Up",
        "Return",                   // return to the menu in the main function
        "Exit",                    // exit the app
        NULL};

    int choice = choose_item(Choices, "Make your choice");

    switch (choice)
    {
    case 0:
        logIn_Client();
        break;
    case 1:
        signUpRequest();
        break;
    case 2:
        main();
        break;
    default:
        exit(0);
        break;
    }
}

char CIN[9] = {'\0'};

void requestCIN() // (8 caraters long) + (first alpha) + (second alpha or num) + (rest num)
{
    while (1)
    {
        printf("Enter your CIN: ");
        scanf(" %8s", CIN);

        // Validate CIN
        if (isValidCIN(CIN))
            break;
        else
            printf(RED "Invalid CIN. Please try again.\n" RESET);
    }
}

int isValidCIN(char *cin)
{
    // Check length
    if (strlen(cin) != sizeof(CIN)-1)
        return 0;

    // Validate first character (must be alphabetic)
    if (!isalpha(cin[0]))
        return 0;

    // Validate second character (must be alphanumeric)
    if (!isalnum(cin[1]))
        return 0;

    // Validate the remaining six characters (must be numeric)
    for (int i = 2; i < 8; i++)
    {
        if (!isdigit(cin[i]))
            return 0;
    }

    return 1; // Valid CIN
}

// fonction afficher cin f1********

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
        printf(ORANGE "Client with CIN: %s not found.\n" RESET, CIN);
        printf("1 - Retry CIN\n2 - Request Sign Up\n");

        int choice;
        scanf("%1d", &choice);

        // while: invalid CIN or choice, or no request to sign up
        switch (choice)
        {
        case 1:
            requestCIN();
            client = findClientByCIN(CIN);
            break;
        case 2:
            signUpRequest();
            // client = findClientByCIN(CIN); not necessary
            break;
        default:
            printf(RED "Invalid choice. Please enter 1 or 2.\n" RESET);
            break;
        }
    }

    authenticateClient(client);
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
            if(checkClientApprovalStatus(client))
            {
                // If no issues, grant access
                printf(CYAN "\nWelcome, %s! Accessing BANK MANAGEMENT SYSTEM...\n" RESET, client->name);
                displayClientDetails(client);
                logIn_Account(client->clientID);            //TODO:
            }
        }
        else
        {
            printf(ORANGE "Incorrect PIN. Please try again.\n" RESET);
            attemptCount++;
        }
    }
    printf(YELLOW "Too many failed attempts. Exiting...\n" RESET); // Just a simple message with no procedures
    return;
}

int checkClientApprovalStatus(Client *client)
{
    // Check if the client's account request is still pending :  0 - inactive , 1 - Active
    if (!client->activation)
    {
        printf(ORANGE "Your account is still pending approval. Please wait for an update from the bank.\n" RESET "However, you can view your client details.\n" RED "If any information in details below is incorrect, please submit a new account creation request.\n" RESET);
        displayClientDetails(client);
        exit(0);
    }
    return 1;
}

void signUpRequest()
{
    if (strcmp(CIN, "\0") == 0)
    {
        requestCIN();
    }

    if (findClientByCIN(CIN) != NULL)
    {
        printf(BLUE "Client with CIN %s already exists. Redirecting to login...\n" RESET, CIN);
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
    int check = false;

    printf(BLUE "Requesting client creation...\n" RESET);

    while (!check)
    {
        printf("Enter Client Name: ");
        scanf(" %[^\n]", newClient.name);
        check = isAlphaString(newClient.name);
    }
    check = false;

    strncpy(newClient.CIN, CIN, sizeof(newClient.CIN) - 1);
    newClient.CIN[sizeof(newClient.CIN) - 1] = '\0';
    
    while (!check)
    {
        printf("Enter Client Phone Number: ");
        scanf(" %[^\n]", newClient.phoneNumber);
        check = (isNumericString(newClient.phoneNumber) && (strlen(newClient.phoneNumber) == 10) && (newClient.phoneNumber[0] == '0'));
    }
    check = false;


    printf("Enter Client Address: ");
    scanf(" %[^\n]", newClient.address);

    newClient.Blacklisted = 0;
    newClient.activation = 0;

    setAndConfirmPIN(newClient.PIN);

    newClient.clientID = generateRandomAccountNumber();
    printf("Your Client ID: %lld\n", newClient.clientID);

    getCurrentDate(newClient.dateCreated, sizeof(newClient.dateCreated));
    printf("Client request created on: %s\n", newClient.dateCreated);

    saveRequestToFile(&newClient);
    exit(0);

}

Client *findClientByCIN(char *CIN)
{
    FILE *file = fopen("clients.dat", "rb");
    if (file == NULL)
    {
        perror(RED "Error opening file ~1~\n" RESET); // Detailed error for debugging : ~1~
        printf(RED "We're sorry, but we encountered a technical issue while accessing client data. Please try again later or contact support.\n" RESET);
        exit(EXIT_FAILURE); // Exit program if file cannot be opened
    }

    Client *client = malloc(sizeof(Client));
    if (client == NULL)
    {
        perror(RED "Memory allocation failed ~2~\n" RESET); // Detailed error for debugging : ~2~
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
        fclose(file);
        exit(EXIT_FAILURE); // Exit program if memory allocation fails
    }

    while (fread(client, sizeof(Client), 1, file) == 1)
    {
        if (strcmp(client->CIN, CIN) == 0)
        {
            fclose(file);
            return client; // Return the client if CIN matches
        }
    }

    free(client); // Free allocated memory if no match is found
    fclose(file);
    return NULL; // Return NULL if the CIN is not found
}

void requestClientModification(Client *existingClient) {
    Client modifiedClient;
    memcpy(&modifiedClient, existingClient, sizeof(Client)); // Copie des données existantes pour modification

    printf(BLUE "Requesting modification of client details...\n" RESET);

    // Modification du nom
    printf("Current Name: %s\n", existingClient->name);
    printf("Enter new Name (press Enter to keep current): ");
    char nameInput[100];
    fgets(nameInput, sizeof(nameInput), stdin);
    nameInput[strcspn(nameInput, "\n")] = '\0'; // Suppression du saut de ligne
    if (strlen(nameInput) > 0) {
        strncpy(modifiedClient.name, nameInput, sizeof(modifiedClient.name) - 1);
    }

    // Modification du numéro de téléphone
    printf("Current Phone Number: %s\n", existingClient->phoneNumber);
    printf("Enter new Phone Number (press Enter to keep current): ");
    char phoneInput[15];
    fgets(phoneInput, sizeof(phoneInput), stdin);
    phoneInput[strcspn(phoneInput, "\n")] = '\0';
    if (strlen(phoneInput) > 0 && isNumericString(phoneInput) && strlen(phoneInput) == 10) {
        strncpy(modifiedClient.phoneNumber, phoneInput, sizeof(modifiedClient.phoneNumber) - 1);
    }

    // Modification de l'adresse
    printf("Current Address: %s\n", existingClient->address);
    printf("Enter new Address (press Enter to keep current): ");
    char addressInput[200];
    fgets(addressInput, sizeof(addressInput), stdin);
    addressInput[strcspn(addressInput, "\n")] = '\0';
    if (strlen(addressInput) > 0) {
        strncpy(modifiedClient.address, addressInput, sizeof(modifiedClient.address) - 1);
    }

    // Comparaison des données
    printf(BLUE "\nComparison of Changes:\n" RESET);
    printf("Name: ");
    if (strcmp(existingClient->name, modifiedClient.name) == 0) {
        printf(GREEN "No change (%s)\n" RESET, existingClient->name);
    } else {
        printf(RED "Old: %s -> New: %s\n" RESET, existingClient->name, modifiedClient.name);
    }

    printf("Phone Number: ");
    if (strcmp(existingClient->phoneNumber, modifiedClient.phoneNumber) == 0) {
        printf(GREEN "No change (%s)\n" RESET, existingClient->phoneNumber);
    } else {
        printf(RED "Old: %s -> New: %s\n" RESET, existingClient->phoneNumber, modifiedClient.phoneNumber);
    }

    printf("Address: ");
    if (strcmp(existingClient->address, modifiedClient.address) == 0) {
        printf(GREEN "No change (%s)\n" RESET, existingClient->address);
    } else {
        printf(RED "Old: %s -> New: %s\n" RESET, existingClient->address, modifiedClient.address);
    }

    // Confirmation et sauvegarde de la demande
    printf(YELLOW "\nDo you want to submit this modification request? (1 - Yes, 0 - No): " RESET);
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        saveRequestToFile(&modifiedClient);
        printf(GREEN "Your modification request has been submitted for review.\n" RESET);
    } else {
        printf(ORANGE "Modification request canceled.\n" RESET);
    }
}

void saveRequestToFile(Client *client)
{
    FILE *file = fopen("client_requests.dat", "rb+");
    if (file == NULL)
    {
        perror(RED "Error opening the request file ~3~\n" RESET);   // ~3~
        printf(RED "We're sorry, but your request could not be saved due to a technical issue. Please try again later or contact customer support.\n" RESET);
        exit(EXIT_FAILURE);
    }

    Client existingClient;
    int found = 0;
    long position = 0;

    // Search for an existing request with the same CIN
    while (fread(&existingClient, sizeof(Client), 1, file) == 1)
    {
        if (strcmp(existingClient.CIN, client->CIN) == 0)
        {
            found = 1;
            break;
        }
        position += sizeof(Client);
    }

    if (found)
    {
        printf(ORANGE "A request with CIN %s already exists.\n" RESET, client->CIN);
        printf("1 - Cancel the new request and keep the old one\n");
        printf("2 - Replace the old request with the new one\n");
        printf("3 - Cancel both the new and old requests\n");

        int choice;
        scanf("%1d", &choice);

        if (choice == 1)
        {
            printf(GREEN "The new request has been canceled, and the old version remains unchanged.\n" RESET);
            fclose(file);
            return;
        }
        else if (choice == 2)
        {
            fseek(file, position, SEEK_SET); // Move to the position of the old request
            fwrite(client, sizeof(Client), 1, file); // Overwrite with the new request
            printf(GREEN "The old request has been replaced with the new one successfully.\n" RESET);
            fclose(file);
            return;
        }
        else if (choice == 3)
        {
            FILE *tempFile = fopen("temp.dat", "wb");
            if (tempFile == NULL)
            {
                perror(RED "Error creating a temporary file ~4~\n" RESET);  // ~4~
                fclose(file);
                exit(EXIT_FAILURE);
            }

            // Rewind to the start of the file
            rewind(file);

            // Copy all requests except the current one (to be canceled) to the temporary file
            while (fread(&existingClient, sizeof(Client), 1, file) == 1)
            {
                if (strcmp(existingClient.CIN, client->CIN) != 0)
                {
                    fwrite(&existingClient, sizeof(Client), 1, tempFile);
                }
            }

            fclose(file);
            fclose(tempFile);

            // Replace the original file with the updated one
            remove("client_requests.dat");
            rename("temp.dat", "client_requests.dat");

            printf(GREEN "Both the new and old requests have been canceled successfully.\n" RESET);
            return;
        }
        else
        {
            printf(YELLOW "Invalid choice. No changes were made.\n" RESET);
            fclose(file);
            return;
        }
    }
    else
    {
        // Append the new request if no duplicate is found
        fseek(file, 0, SEEK_END);
        fwrite(client, sizeof(Client), 1, file);
        printf(GREEN "Your request has been saved successfully and is pending approval.\n" RESET);
    }

    fclose(file);
}

void processClientRequest() {
    FILE *requestFile = fopen("client_requests.dat", "rb");
    if (requestFile == NULL) {
        printf(BLUE "No pending client requests.\n" RESET);
        return;
    }

    FILE *tempFile = fopen("temp_requests.dat", "wb");
    if (tempFile == NULL) {
        printf(RED "Error opening temporary file ~5~\n" RESET); // ~5~
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
        fclose(requestFile);
        return;
    }

    Client client;
    int hasRequests = 0;

    while (fread(&client, sizeof(Client), 1, requestFile) == 1) {
        hasRequests = 1;
        printf(BLUE "Reviewing Request for Client:\n" RESET);
        displayClientDetails(&client);

        printf(PURPLE "Approve this client? (1 - Approve, 2 - Reject): " RESET);
        int choice;
        scanf("%1d", &choice);

        if (choice == 1) {
            saveClientToFile(&client); // Move to 'clients.dat'
            printf(GREEN "Client approved and moved to client database.\n" RESET);
        } else if (choice == 2) {
            printf(ORANGE "Client request rejected and deleted.\n" RESET);
        } else {
            printf(YELLOW "Invalid choice. Skipping this request.\n" RESET);
            fwrite(&client, sizeof(Client), 1, tempFile); // Save back to requests
        }
    }

    fclose(requestFile);
    fclose(tempFile);

    if (!hasRequests) {
        printf(BLUE "No pending client requests found.\n" RESET);
        remove("temp_requests.dat");
        return;
    }

    // Replace old request file with updated one
    remove("client_requests.dat");
    rename("temp_requests.dat", "client_requests.dat");
    printf(BLUE "Processed all client requests.\n" RESET);
}

void reviewAccountUpdateRequest() {
    FILE *requestFile = fopen("account_update_requests.dat", "rb");
    if (requestFile == NULL) {
        printf(BLUE "No pending account update requests.\n" RESET);
        return;
    }

    FILE *tempFile = fopen("temp_account_updates.dat", "wb");
    if (tempFile == NULL) {
        printf(RED "Error opening temporary file.\n" RESET);
        fclose(requestFile);
        return;
    }

    Client oldClient, newClient;
    int hasRequests = 0;

    while (fread(&newClient, sizeof(Client), 1, requestFile) == 1) {
        hasRequests = 1;

        // Retrieve the old account details
        Client *oldClientPointer = findClientByCIN(newClient.CIN);
        if (oldClientPointer == NULL) {
            printf(RED "Original client details not found for CIN: %s\n" RESET, newClient.CIN);
            fwrite(&newClient, sizeof(Client), 1, tempFile); // Save back for further processing
            continue;
        }
        oldClient = *oldClientPointer;

        printf(BLUE "\nReviewing Account Update Request for CIN: %s\n" RESET, newClient.CIN);

        // Highlight the differences between old and new accounts
        printf(YELLOW "Comparison of Account Details:\n" RESET);

        printf("Name: ");
        if (strcmp(oldClient.name, newClient.name) == 0)
            printf(GREEN "%s\n" RESET, oldClient.name);
        else
            printf(RED "Old: %s | New: %s\n" RESET, oldClient.name, newClient.name);

        printf("Phone Number: ");
        if (strcmp(oldClient.phoneNumber, newClient.phoneNumber) == 0)
            printf(GREEN "%s\n" RESET, oldClient.phoneNumber);
        else
            printf(RED "Old: %s | New: %s\n" RESET, oldClient.phoneNumber, newClient.phoneNumber);

        printf("Address: ");
        if (strcmp(oldClient.address, newClient.address) == 0)
            printf(GREEN "%s\n" RESET, oldClient.address);
        else
            printf(RED "Old: %s | New: %s\n" RESET, oldClient.address, newClient.address);

        printf(PURPLE "Approve this account update? (1 - Approve, 2 - Reject): " RESET);
        int choice;
        scanf("%1d", &choice);

        if (choice == 1) {
            saveClientToFile(&newClient); // Save the updated client details to the client file
            printf(GREEN "Account update approved and saved.\n" RESET);
        } else if (choice == 2) {
            printf(ORANGE "Account update request rejected and deleted.\n" RESET);
        } else {
            printf(YELLOW "Invalid choice. Skipping this request.\n" RESET);
            fwrite(&newClient, sizeof(Client), 1, tempFile); // Save back for further processing
        }
    }

    fclose(requestFile);
    fclose(tempFile);

    if (!hasRequests) {
        printf(BLUE "No pending account update requests found.\n" RESET);
        remove("temp_account_updates.dat");
        return;
    }

    // Replace old request file with updated one
    remove("account_update_requests.dat");
    rename("temp_account_updates.dat", "account_update_requests.dat");
    printf(BLUE "Processed all account update requests.\n" RESET);
}

/*
void processAccountRequests() {
    FILE *requestFile = fopen("account_requests.dat", "rb");
    if (requestFile == NULL) {
        printf(BLUE "No pending account requests.\n" RESET);
        return;
    }

    FILE *tempFile = fopen("temp_account_requests.dat", "wb");
    if (tempFile == NULL) {
        printf(RED "Error opening temporary file.\n" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
        fclose(requestFile);
        return;
    }

    Account accountRequest;
    int hasRequests = 0;

    while (fread(&accountRequest, sizeof(Account), 1, requestFile) == 1) {
        hasRequests = 1;
        printf(BLUE "Reviewing Account Request:\n" RESET);
        displayAccountDetails(&accountRequest); // Assuming you have a function to display account details.

        printf(PURPLE "Approve this account request? (1 - Approve, 2 - Reject): " RESET);
        int choice;
        scanf("%1d", &choice);

        if (choice == 1) {
            saveAccountToFile(&accountRequest); // Move to 'accounts.dat'
            printf(GREEN "Account approved and moved to account database.\n" RESET);
        } else if (choice == 2) {
            printf(ORANGE "Account request rejected and deleted.\n" RESET);
        } else {
            printf(YELLOW "Invalid choice. Skipping this request.\n" RESET);
            fwrite(&accountRequest, sizeof(Account), 1, tempFile); // Save back to requests
        }
    }

    fclose(requestFile);
    fclose(tempFile);

    if (!hasRequests) {
        printf(BLUE "No pending account requests found.\n" RESET);
        remove("temp_account_requests.dat");
        return;
    }

    // Replace old request file with updated one
    remove("account_requests.dat");
    rename("temp_account_requests.dat", "account_requests.dat");
    printf(BLUE "Processed all account requests.\n" RESET);
}
*/

void saveClientToFile(Client *client)
{
    FILE *file = fopen("clients.dat", "ab");
    if (file == NULL)
    {
        printf(RED "Failed to open file for saving client.\n" RESET);
        printf(RED "A critical error occurred while processing your request. Please try again later or contact support.\n" RESET);
    }

    fwrite(client, sizeof(Client), 1, file);
    fclose(file);
    printf(GREEN "Client saved successfully!\n" RESET);
}

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
        perror(RED "Error opening clients file" RESET);
        printf(RED "Unable to access the client database. Please report this issue to the technical team for resolution.\n" RESET);
        return; // Exit the function gracefully
    }

    Client client;
    int count = 0;

    printf(PURPLE "\n--- All Clients ---\n" RESET);
    printf("%-5s %-20s %-15s %-15s %-20s %-12s %-10s %-25s\n",
           "No", "Client ID", "CIN", "Name", "Phone Number", "Blacklisted", "Pending", "Date Created");
    printf(PURPLE "----------------------------------------------------------------------------------------------------\n" RESET);

    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        count++;
        printf("%-5d %-20lld %-15s %-15s %-20s %-12s %-10s %-25s\n",
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

    if (count == 0)
    {
        printf(YELLOW "No clients found in the database.\n" RESET);
    }
    else
    {
        printf(GREEN "\nDisplayed %d client(s) successfully.\n" RESET, count);
    }
}
