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
        fseek(file, -(long)sizeof(Employee), SEEK_CUR);  // Cast to long to avoid overflow warning
        fwrite(loggedInEmployee, sizeof(Employee), 1, file);
        printf(GREEN "Employee details updated successfully in the file.\n" RESET);
        break;
    }
}

        fclose(file);
    }
}



void deleteEmployee(Employee *loggedInEmployee)
{
    // Ensure the user has logged in and is an admin
    if (loggedInEmployee == NULL || loggedInEmployee->isAdmin != 1)
    {
        printf(RED "ERROR: Access Denied.\n" RESET);
        printf(YELLOW "Only admin users can delete employees.\n" RESET);
        return;
    }

    FILE *file = fopen("employees.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (file == NULL || tempFile == NULL)
    {
        printf(RED "ERROR: Failed to access employee database.\n" RESET);
        printf(YELLOW "Please report this issue to the technical team.\n" RESET);
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    long long targetEmployeeID;
    printf(BLUE "Enter the Employee ID to delete: " RESET);
    scanf("%lld", &targetEmployeeID);

    Employee employee;
    int isDeleted = 0;

    // Read employees and copy only non-matching ones to the temporary file
    while (fread(&employee, sizeof(Employee), 1, file) == 1)
    {
        if (employee.employeeID == targetEmployeeID)
        {
            isDeleted = 1; // Mark as deleted
            printf(GREEN "Employee with ID %lld successfully deleted.\n" RESET, targetEmployeeID);
        }
        else
        {
            fwrite(&employee, sizeof(Employee), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated temporary file
    if (isDeleted)
    {
        remove("employees.dat");
        rename("temp.dat", "employees.dat");
    }
    else
    {
        printf(ORANGE "No employee found with ID %lld.\n" RESET, targetEmployeeID);
        remove("temp.dat");
    }
}
