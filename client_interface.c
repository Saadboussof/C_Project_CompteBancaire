#include "client.h"

char CIN[9] = {'\0'};

void Client_Portal()
{
    memset(CIN, '\0', sizeof(CIN));
    char *Choices[] = {
        "Log in",
        "Sign Up",
        "Return", // return to the menu in the main function
        "Exit",   // exit the app
        NULL};

    int choice = choose_item(Choices, "Client Portal");

    while (1)
    {
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
}

void requestCIN() // (8 caraters long) + (first alpha) + (second alpha or num) + (rest num)
{
    while (1)
    {
        printf("Enter your CIN: ");
        scanf("%s", CIN);

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
    if (strlen(cin) != sizeof(CIN) - 1)
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

void logIn_Client()
{
    // Request CIN if it's not already provided
    if (strcmp(CIN, "\0") == 0)
    {
        requestCIN();
    }

    // Attempt to find client by CIN
    Client *client = findClient(CIN, 0, 1);

    while (client == NULL)
    {
        printf(ORANGE "Client with CIN: %s not found.\n" RESET, CIN);
        printf("1- Retry CIN\n2- Request Sign Up\n");

        char choice;
        choice = getch();
        printf("\n");

        // while: invalid CIN or choice, or no request to sign up
        switch (choice)
        {
        case '1':
            fordelay(600000000);
            system("cls");
            requestCIN();
            client = findClient(CIN, 0, 1);
            break;
        case '2':
            signUpRequest();
            client = findClient(CIN, 0, 1);
            break;
        default:
            printf(RED "Invalid choice. Please enter 1 or 2.\n" RESET);
            fordelay(600000000);
            system("cls");
            break;
        }
    }

    if (authenticateClient(client) && checkClientApprovalStatus(client))
    {
        // If no issues, grant access
        printf(CYAN "\nWelcome, %s!\nAccessing BANK MANAGEMENT SYSTEM" RESET, client->name);
        for (int i = 0; i <= 6; i++)
        {
            fordelay(100000000);
            printf(CYAN BOLD "." RESET);
        }
        printf("\n");
        fordelay(1200000000);
        displayClientDetails(client);
        logIn_Account(client->clientID);
    };
    return;
}

int authenticateClient(Client *client)
{
    char PIN[5];
    int attemptCount = 0;

    while (attemptCount < attemptCount_LIMIT)
    {
        printf("Enter your PIN: ");
        PIN_hide(PIN, sizeof(PIN));

        if (validatePIN(client->PIN, PIN))
        {
            printf(GREEN "Correct PIN\n" RESET);
            return 1;
        }
        else
        {
            printf(RED "Incorrect PIN. Please try again.\n" RESET);
            attemptCount++;
        }
    }
    printf(ORANGE "Too many failed attempts. Exiting...\n" RESET); // The program exit
    Client_Portal();
}

int checkClientApprovalStatus(Client *client)
{
    // Check if the client's account is active :  0 - inactive , 1 - Active
    if (!client->activation)
    {
        printf(ORANGE "Your account is still pending approval. Please wait for an update from the bank.\n" RESET "However, you can view your client details.\n" RED "If any information in details below is incorrect, click 1 and update it.\n" RESET);
        
        displayClientDetails(client);
        
        char choice;
        choice = getch();
        printf("\n");
        if (choice == '1')
            updateClient(client->CIN);
        Client_Portal();
        return 0;
    }
    return 1;
}

void signUpRequest()
{
    if (strcmp(CIN, "\0") == 0)
    {
        requestCIN();
    }

    if (findClient(CIN, 0, 1) != NULL)
    {
        printf("Client with CIN : "ORANGE"%s"RESET" already existe.\n", CIN);
        printf(BLUE"Redirecting to login"RESET);
        for (int i = 0; i <= 6; i++)
        {
            fordelay(100000000);
            printf(BLUE BOLD "." RESET);
        }
        printf("\n");
        logIn_Client();
    }
    else
    {
        Client newClient = createClient();
        if(saveClientToFile(&newClient)) {
            printf(GREEN "Client saved successfully!\n" RESET);
            fordelay(1200000000);
            system("cls");
        }
        Client_Portal();
    }
}

Client createClient()
{
    Client newClient;
    int check = false;

    fordelay(600000000);
    system("cls");

    printf(BLUE "Requesting client creation" RESET);
    for (int i = 0; i <= 6; i++)
    {
        fordelay(100000000);
        printf(BLUE BOLD "." RESET);
    }
    printf("\n");

    while (!check)
    {
        printf("Enter Client Name: " GREEN);
        scanf(" %[^\n]", newClient.name);
        check = isAlphaString(newClient.name);
        if (!check)
            printf(RED "Invalide name please try again.\n" RESET);
    }
    check = false;

    strncpy(newClient.CIN, CIN, sizeof(newClient.CIN) - 1);
    newClient.CIN[sizeof(newClient.CIN) - 1] = '\0';

    while (!check)
    {
        printf(RESET"Enter Client Phone Number: "GREEN);
        scanf(" %[^\n]", newClient.phoneNumber);
        check = (isNumericString(newClient.phoneNumber) && (strlen(newClient.phoneNumber) == 10) && (newClient.phoneNumber[0] == '0'));
        if (!check)
            printf(RESET RED "Invalide Phone Number please try again.\n" RESET);
    }
    check = false;

    printf(RESET"Enter Client Address: "GREEN);
    scanf(" %[^\n]", newClient.address);
    printf(RESET"");

    newClient.Blacklisted = 0;
    newClient.activation = 1;   // TODO: test

    setAndConfirmPIN(newClient.PIN);

    newClient.clientID = generateRandomAccountNumber();
    printf("Your Client ID: "BOLD"%lld\n"RESET, newClient.clientID);

    getCurrentDate(newClient.dateCreated, sizeof(newClient.dateCreated));
    printf("Client request created on: %s\n", newClient.dateCreated);

    return newClient;
}

void updateClient(char *cin)
{
    FILE *file = fopen("clients.dat", "rb");

    if (file == NULL)
    {
        printf(RED "ERROR: Failed to open the client database.\n" RESET);
        printf(RED "A critical error occurred while processing your request.\n" BOLD "Please try again later or contact support.\n" RESET);

        return;
    }

    FILE *tempFile = fopen("temp_clients.dat", "wb");

    if (tempFile == NULL)
    {
        printf(RED "ERROR: Failed to create the temporary file.\n" RESET);
        printf(RED "A critical error occurred while processing your request.\n" BOLD "Please try again later or contact support.\n" RESET);

        fclose(file);

        return;
    }

    Client client;
    int found = 0;

    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        if (strcmp(client.CIN, cin) == 0)
        {
            found = 1;
            int a = 1;
            while (a)
            {
                printf(YELLOW "Which field would you like to modify?\n" RESET);
                printf("0 -  Skip\n");
                printf("1 -  Phone Number\n");
                printf("2 -  Address\n");

                char choice;
                choice = getch();
                printf("\n");

                switch (choice)
                {
                case '0':
                {
                    a = 0;
                    break;
                }
                case '1':
                {
                    if (authenticateClient(&client))
                    {
                        char newPhone[11];
                        int valid = 0;
                        while (!valid)
                        {
                            printf("Enter new Phone Number: ");
                            scanf(" %[^\n]", newPhone);

                            valid = isNumericString(newPhone) && strlen(newPhone) == 10 && newPhone[0] == '0';

                            if (!valid)
                                printf(RED "Invalid phone number. Please try again.\n" RESET);
                        }
                        strncpy(client.phoneNumber, newPhone, sizeof(client.phoneNumber) - 1);
                        client.phoneNumber[sizeof(client.phoneNumber) - 1] = '\0';
                        printf(GREEN "Phone number updated successfully.\n" RESET);
                    }
                    break;
                }
                case '2':
                {
                    char newAddress[50];
                    printf("Enter new Address: ");
                    scanf(" %[^\n]", newAddress);
                    strncpy(client.address, newAddress, sizeof(client.address) - 1);
                    client.address[sizeof(client.address) - 1] = '\0';
                    printf(GREEN "Address updated successfully.\n" RESET);
                    break;
                }
                default:
                    printf(ORANGE "Invalid choice. No changes were made.\n" RESET);
                    break;
                }
                fordelay(900000000);
            }
        }

        // Write the current (modified or unmodified) client to the temp file
        fwrite(&client, sizeof(Client), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf(ORANGE "No client found with CIN: %s\n" RESET, cin);
        remove("temp_clients.dat"); // Remove the temp file if no client was found
        return;
    }

    // Replace the main file with the updated temp file
    remove("clients.dat");
    rename("temp_clients.dat", "clients.dat");

    printf(GREEN "Client details updated successfully in the database.\n" RESET);
    fordelay(1000000000);
    system("cls");
    return;
}

void viewProcedInactive()
{
    displayFilteredClients(1, 0);
    processClientRequest();
}