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
    PIN_hide(currentPassword, sizeof(currentPassword));

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
            PIN_hide(newPassword, sizeof(newPassword));
            strncpy(loggedInEmployee->password, newPassword, sizeof(loggedInEmployee->password) - 1);
            loggedInEmployee->password[sizeof(loggedInEmployee->password) - 1] = '\0';
            printf(GREEN "Password updated successfully.\n" RESET);
            break;
        }

        case 1: // Update phone number
        {
            char newPhoneNumber[11];
            int check = false;
            while (!check)
    {
        printf("Enter Client Phone Number: ");
        scanf(" %[^\n]", newPhoneNumber);
        check = (isNumericString(newPhoneNumber) && (strlen(newPhoneNumber) == 10) && (newPhoneNumber[0] == '0'));
        if (!check)
            printf(RED "Invalide Phone Number please try again.\n" RESET);
    }
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

