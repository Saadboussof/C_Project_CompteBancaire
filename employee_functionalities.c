<<<<<<< HEAD
#include "employee.h"

void viewClientRequests()
{
    printf("\n--- Viewing Pending Client Requests ---\n");

    FILE *file = fopen("temp_requests.dat", "rb");
    if (file == NULL)
    {
        printf(RED "ERROR: Unable to access client requests file.\n" RESET);
        return;
    }

    Client client;
    int found = 0;
    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        if (client.activation == 0) // Assuming activation == 0 means "pending request"
        {
            found = 1;
            printf("CIN: %s | Name: %s | Phone: %s | Address: %s\n",
                   client.CIN, client.name, client.phoneNumber, client.address);
        }
    }

    if (!found)
        printf(GREEN "No pending client requests found.\n" RESET);

    fclose(file);
}



// void approveRejectClient()
// {
//     printf("\n--- Approve/Reject Client Requests ---\n");

//     char CIN[10];
//     printf("Enter the CIN of the client to process: ");
//     scanf(" %[^\n]", CIN);

//     FILE *file = fopen("client_requests.dat", "rb+");
//     if (file == NULL)
//     {
//         printf(RED "ERROR: Unable to access client requests file.\n" RESET);
//         return;
//     }

//     Client client;
//     int found = 0;
//     while (fread(&client, sizeof(Client), 1, file) == 1)
//     {
//         if (strcmp(client.CIN, CIN) == 0 && client.activation == 0)
//         {
//             found = 1;
//             int choice;
//             printf("Client CIN: %s\nName: %s\nPhone: %s\nAddress: %s\n",
//                    client.CIN, client.name, client.phoneNumber, client.address);

//             printf("Approve [1] or Reject [2]? ");
//             scanf("%d", &choice);

//             if (choice == 1)
//             {
//                 client.activation = 1; // Approve client
//                 fseek(file, sizeof(Client), SEEK_CUR); // Move file pointer to update record
//                 fwrite(&client, sizeof(Client), 1, file);
//                 printf(GREEN "Client account approved.\n" RESET);
//             }
//             else if (choice == 2)
//             {
//                 printf(RED "Client account rejected.\n" RESET);
//                 // Logic to skip saving this client can be added
//             }
//             else
//             {
//                 printf(RED "Invalid choice. Operation canceled.\n" RESET);
//             }
//             break;
//         }
//     }

//     if (!found)
//         printf(RED "No pending client request found with CIN: %s.\n" RESET, CIN);

//     fclose(file);
// }



// void manageClients()
// {
//     printf("\n--- Manage Clients ---\n");

//     char CIN[10];
//     printf("Enter the CIN of the client to manage: ");
//     scanf(" %[^\n]", CIN);

//     FILE *file = fopen("clients.dat", "rb+");
//     if (file == NULL)
//     {
//         printf(RED "ERROR: Unable to access clients file.\n" RESET);
//         return;
//     }

//     Client client;
//     int found = 0;
//     while (fread(&client, sizeof(Client), 1, file) == 1)
//     {
//         if (strcmp(client.CIN, CIN) == 0)
//         {
//             found = 1;

//             printf("Client CIN: %s\nName: %s\nPhone: %s\nAddress: %s\n",
//                    client.CIN, client.name, client.phoneNumber, client.address);

//             int choice;
//             printf("Choose an action:\n[1] Edit Client\n[2] Delete Client\n");
//             scanf("%d", &choice);

//             if (choice == 1)
//             {
//                 printf("Enter new phone number: ");
//                 scanf(" %[^\n]", client.phoneNumber);
//                 printf("Enter new address: ");
//                 scanf(" %[^\n]", client.address);

//                 fseek(file, sizeof(Client), SEEK_CUR);
//                 fwrite(&client, sizeof(Client), 1, file);
//                 printf(GREEN "Client details updated successfully.\n" RESET);
//             }
//             else if (choice == 2)
//             {
//                 printf(RED "Deleting client record is currently unsupported.\n" RESET);
//                 // Optional deletion logic can go here
//             }
//             else
//             {
//                 printf(RED "Invalid choice.\n" RESET);
//             }
//             break;
//         }
//     }

//     if (!found)
//         printf(RED "No client found with CIN: %s.\n" RESET, CIN);

//     fclose(file);
// }

// Employee *loggedInEmployee1;


void updateEmployeeDetails(Employee *loggedInEmployee)
{
    printf("\n--- Update Employee Details ---\n");

    if (loggedInEmployee == NULL)
    {
        printf(RED "You need to log in to update your details.\n" RESET);
        return;
    }

    // Verify the current password
    char currentPassword[20];
    printf("Enter current password to confirm identity: ");
    scanf(" %[^\n]", currentPassword);

    if (strcmp(loggedInEmployee->password, currentPassword) != 0)
    {
        printf(RED "Incorrect current password.\n" RESET);
        return;
    }

    // Choices for updating details
    char *Choices[] = {
        "Change Password",
        "Update Phone Number",
        "Update Address",
        "Exit",   // Exit the menu
        NULL};

    int choice;

    while (1)
    {
        choice = choose_item(Choices, "Update Employee Details: Select an option");

        switch (choice)
        {
        case 0: // Change password
        {
            char newPassword[20];
            printf("Enter new password: ");
            scanf(" %[^\n]", newPassword);
            strncpy(loggedInEmployee->password, newPassword, sizeof(loggedInEmployee->password) - 1);
            loggedInEmployee->password[sizeof(loggedInEmployee->password) - 1] = '\0';
            printf(GREEN "Password updated successfully.\n" RESET);
            break;
        }

        case 1: // Update phone number
        {
            char newPhoneNumber[11];
            printf("Enter new phone number: ");
            scanf(" %[^\n]", newPhoneNumber);
            strncpy(loggedInEmployee->E_phone_number, newPhoneNumber, sizeof(loggedInEmployee->E_phone_number) - 1);
            loggedInEmployee->E_phone_number[sizeof(loggedInEmployee->E_phone_number) - 1] = '\0';
            printf(GREEN "Phone number updated successfully.\n" RESET);
            break;
        }

        case 2: // Update address
        {
            char newAddress[50];
            printf("Enter new address: ");
            scanf(" %[^\n]", newAddress);
            strncpy(loggedInEmployee->E_adresse, newAddress, sizeof(loggedInEmployee->E_adresse) - 1);
            loggedInEmployee->E_adresse[sizeof(loggedInEmployee->E_adresse) - 1] = '\0';
            printf(GREEN "Address updated successfully.\n" RESET);
            break;
        }

        case 3: // Exit
            printf(YELLOW "Exiting update menu.\n" RESET);
            return;

        default:
            printf(RED "Invalid choice. Please try again.\n" RESET);
            break;
        }

        // Update the file after each change
        FILE *file = fopen("employees.dat", "rb+");
        if (file == NULL)
        {
            printf(RED "ERROR: Failed to update employee details in the file.\n" RESET);
            return;
        }

        Employee employee;
        while (fread(&employee, sizeof(Employee), 1, file) == 1)
        {
            if (employee.employeeID == loggedInEmployee->employeeID)
            {
                fseek(file, -sizeof(Employee), SEEK_CUR);
                fwrite(loggedInEmployee, sizeof(Employee), 1, file);
                printf(GREEN "Employee details updated successfully in the file.\n" RESET);
                break;
            }
        }
        fclose(file);
    }
}

=======
#include "employee.h"

void viewClientRequests()
{
    printf("\n--- Viewing Pending Client Requests ---\n");

    FILE *file = fopen("temp_requests.dat", "rb");
    if (file == NULL)
    {
        printf(RED "ERROR: Unable to access client requests file.\n" RESET);
        return;
    }

    Client client;
    int found = 0;
    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        if (client.activation == 0) // Assuming activation == 0 means "pending request"
        {
            found = 1;
            printf("CIN: %s | Name: %s | Phone: %s | Address: %s\n",
                   client.CIN, client.name, client.phoneNumber, client.address);
        }
    }

    if (!found)
        printf(GREEN "No pending client requests found.\n" RESET);

    fclose(file);
}



// void approveRejectClient()
// {
//     printf("\n--- Approve/Reject Client Requests ---\n");

//     char CIN[10];
//     printf("Enter the CIN of the client to process: ");
//     scanf(" %[^\n]", CIN);

//     FILE *file = fopen("client_requests.dat", "rb+");
//     if (file == NULL)
//     {
//         printf(RED "ERROR: Unable to access client requests file.\n" RESET);
//         return;
//     }

//     Client client;
//     int found = 0;
//     while (fread(&client, sizeof(Client), 1, file) == 1)
//     {
//         if (strcmp(client.CIN, CIN) == 0 && client.activation == 0)
//         {
//             found = 1;
//             int choice;
//             printf("Client CIN: %s\nName: %s\nPhone: %s\nAddress: %s\n",
//                    client.CIN, client.name, client.phoneNumber, client.address);

//             printf("Approve [1] or Reject [2]? ");
//             scanf("%d", &choice);

//             if (choice == 1)
//             {
//                 client.activation = 1; // Approve client
//                 fseek(file, sizeof(Client), SEEK_CUR); // Move file pointer to update record
//                 fwrite(&client, sizeof(Client), 1, file);
//                 printf(GREEN "Client account approved.\n" RESET);
//             }
//             else if (choice == 2)
//             {
//                 printf(RED "Client account rejected.\n" RESET);
//                 // Logic to skip saving this client can be added
//             }
//             else
//             {
//                 printf(RED "Invalid choice. Operation canceled.\n" RESET);
//             }
//             break;
//         }
//     }

//     if (!found)
//         printf(RED "No pending client request found with CIN: %s.\n" RESET, CIN);

//     fclose(file);
// }



// void manageClients()
// {
//     printf("\n--- Manage Clients ---\n");

//     char CIN[10];
//     printf("Enter the CIN of the client to manage: ");
//     scanf(" %[^\n]", CIN);

//     FILE *file = fopen("clients.dat", "rb+");
//     if (file == NULL)
//     {
//         printf(RED "ERROR: Unable to access clients file.\n" RESET);
//         return;
//     }

//     Client client;
//     int found = 0;
//     while (fread(&client, sizeof(Client), 1, file) == 1)
//     {
//         if (strcmp(client.CIN, CIN) == 0)
//         {
//             found = 1;

//             printf("Client CIN: %s\nName: %s\nPhone: %s\nAddress: %s\n",
//                    client.CIN, client.name, client.phoneNumber, client.address);

//             int choice;
//             printf("Choose an action:\n[1] Edit Client\n[2] Delete Client\n");
//             scanf("%d", &choice);

//             if (choice == 1)
//             {
//                 printf("Enter new phone number: ");
//                 scanf(" %[^\n]", client.phoneNumber);
//                 printf("Enter new address: ");
//                 scanf(" %[^\n]", client.address);

//                 fseek(file, sizeof(Client), SEEK_CUR);
//                 fwrite(&client, sizeof(Client), 1, file);
//                 printf(GREEN "Client details updated successfully.\n" RESET);
//             }
//             else if (choice == 2)
//             {
//                 printf(RED "Deleting client record is currently unsupported.\n" RESET);
//                 // Optional deletion logic can go here
//             }
//             else
//             {
//                 printf(RED "Invalid choice.\n" RESET);
//             }
//             break;
//         }
//     }

//     if (!found)
//         printf(RED "No client found with CIN: %s.\n" RESET, CIN);

//     fclose(file);
// }

// Employee *loggedInEmployee1;


void updateEmployeeDetails(Employee *loggedInEmployee)
{
    printf("\n--- Update Employee Details ---\n");

    if (loggedInEmployee == NULL)
    {
        printf(RED "You need to log in to update your details.\n" RESET);
        return;
    }

    // Verify the current password
    char currentPassword[20];
    printf("Enter current password to confirm identity: ");
    scanf(" %[^\n]", currentPassword);

    if (strcmp(loggedInEmployee->password, currentPassword) != 0)
    {
        printf(RED "Incorrect current password.\n" RESET);
        return;
    }

    // Choices for updating details
    char *Choices[] = {
        "Change Password",
        "Update Phone Number",
        "Update Address",
        "Exit",   // Exit the menu
        NULL};

    int choice;

    while (1)
    {
        choice = choose_item(Choices, "Update Employee Details: Select an option");

        switch (choice)
        {
        case 0: // Change password
        {
            char newPassword[20];
            printf("Enter new password: ");
            scanf(" %[^\n]", newPassword);
            strncpy(loggedInEmployee->password, newPassword, sizeof(loggedInEmployee->password) - 1);
            loggedInEmployee->password[sizeof(loggedInEmployee->password) - 1] = '\0';
            printf(GREEN "Password updated successfully.\n" RESET);
            break;
        }

        case 1: // Update phone number
        {
            char newPhoneNumber[11];
            printf("Enter new phone number: ");
            scanf(" %[^\n]", newPhoneNumber);
            strncpy(loggedInEmployee->E_phone_number, newPhoneNumber, sizeof(loggedInEmployee->E_phone_number) - 1);
            loggedInEmployee->E_phone_number[sizeof(loggedInEmployee->E_phone_number) - 1] = '\0';
            printf(GREEN "Phone number updated successfully.\n" RESET);
            break;
        }

        case 2: // Update address
        {
            char newAddress[50];
            printf("Enter new address: ");
            scanf(" %[^\n]", newAddress);
            strncpy(loggedInEmployee->E_adresse, newAddress, sizeof(loggedInEmployee->E_adresse) - 1);
            loggedInEmployee->E_adresse[sizeof(loggedInEmployee->E_adresse) - 1] = '\0';
            printf(GREEN "Address updated successfully.\n" RESET);
            break;
        }

        case 3: // Exit
            printf(YELLOW "Exiting update menu.\n" RESET);
            return;

        default:
            printf(RED "Invalid choice. Please try again.\n" RESET);
            break;
        }

        // Update the file after each change
        FILE *file = fopen("employees.dat", "rb+");
        if (file == NULL)
        {
            printf(RED "ERROR: Failed to update employee details in the file.\n" RESET);
            return;
        }

        Employee employee;
        while (fread(&employee, sizeof(Employee), 1, file) == 1)
        {
            if (employee.employeeID == loggedInEmployee->employeeID)
            {
                fseek(file, -sizeof(Employee), SEEK_CUR);
                fwrite(loggedInEmployee, sizeof(Employee), 1, file);
                printf(GREEN "Employee details updated successfully in the file.\n" RESET);
                break;
            }
        }
        fclose(file);
    }
}

>>>>>>> 37ffb8eb5eaa8de37f6f1e7bdde6367bf5dd9583
