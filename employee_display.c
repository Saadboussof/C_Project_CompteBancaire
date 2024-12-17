#include "employee.h"



void displayEmployeeDetails(Employee *employee)
{
    printf(PURPLE "---------- Employee Information ----------\n" RESET);
    printf("Employee ID       : %lld\n", employee->employeeID);
    printf("CIN               : %s\n", employee->CIN_EM);
    printf("Full Name         : %s\n", employee->fullName);
    printf("Phone Number      : %s\n", employee->E_phone_number);
    printf("Address           : %s\n", employee->E_adresse);
    printf("Role              : %s\n", employee->isAdmin ? "Admin" : "Regular Employee");
    printf(PURPLE "------------------------------------------\n" RESET);
}


void displayAllEmployees(Employee *loggedInEmployee)
{
    // Ensure the user has logged in and is an admin
    if (loggedInEmployee == NULL || loggedInEmployee->isAdmin != 1)
    {
        printf(RED "ERROR: Access Denied.\n" RESET);
        printf(YELLOW "Only admin users can view the employee list.\n" RESET);
        return;
    }

    FILE *file = fopen("employees.dat", "rb");
    if (file == NULL)
    {
        printf(RED "ERROR: Failed to open employee file.\n" RESET);
        printf(YELLOW "Unable to access the employee database. Please report this issue to the technical team.\n" RESET);
        return; // Exit the function gracefully
    }

    Employee employee;
    int count = 0;

    // Header
    printf(PURPLE 
    "\n+----------------------------------------- All Employees -----------------------------------------+\n" RESET);

    printf(PURPLE "|" RESET ORANGE " %-3s " RESET PURPLE "|" RESET ORANGE " %-10s " RESET PURPLE "|" RESET ORANGE " %-8s " RESET PURPLE "|" RESET ORANGE " %-20s " RESET PURPLE "|" RESET ORANGE " %-11s " RESET PURPLE "|" RESET ORANGE " %-10s " RESET PURPLE "|" RESET ORANGE " %-10s " RESET PURPLE "|" RESET "\n", 
           "No", "Employee ID", "CIN", "Name", "Phone Number", "Address", "Role");

    printf(PURPLE "+-----------------------------------------------------------------------------------------------+\n" RESET);

    // Reading employees from file and displaying them
    while (fread(&employee, sizeof(Employee), 1, file) == 1)
    {
        count++;
        printf("" PURPLE "|" RESET CYAN " %-3d " RESET PURPLE "|" RESET " %-10lld " PURPLE "|" RESET " %-8s " PURPLE "|" RESET " %-20s " PURPLE "|" RESET " %-11s " PURPLE "|" RESET " %-10s " PURPLE "|" RESET " %-10s " PURPLE "|" RESET "\n",
                count,
                employee.employeeID,
                employee.CIN_EM,
                employee.fullName,
                employee.E_phone_number,
                employee.E_adresse,
                employee.isAdmin ? RED "   Admin   " RESET : GREEN " Regular " RESET);
    }

    fclose(file);

    // Check if no employees were found
    if (count == 0)
    {
        printf(ORANGE "No employees found in the database.\nIf you think there might be an issue, please report it to the technical team.\n" RESET);
    }
    else
    {
        printf(PURPLE "+-----------------------------------------------------------------------------------------------+\n" RESET);
        printf(GREEN "\nDisplayed %d employee(s) successfully.\n" RESET, count);
    }
}


