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
    setCursor(21, 4);
    // Header
    printf(PURPLE "+--------------------------------------------- All Employees ------------------------------------------------------+\n" RESET);
    setCursor(22, 4);
    printf(PURPLE "|" RESET ORANGE " %-3s " RESET PURPLE "|" RESET ORANGE " %-10s " RESET PURPLE "|" RESET ORANGE " %-8s " RESET PURPLE "|" RESET ORANGE " %-30s " RESET PURPLE "|" RESET ORANGE " %-13s " RESET PURPLE "|" RESET ORANGE " %-20s " RESET PURPLE "|" RESET ORANGE " %-9s " RESET PURPLE "|" RESET "\n", 
           "No", "Employee ID", "CIN", "Name", "Phone Number", "Address", "Role");
    setCursor(23, 4);
    printf(PURPLE "+------------------------------------------------------------------------------------------------------------------+\n" RESET);

    // Reading employees from file and displaying them
    while (fread(&employee, sizeof(Employee), 1, file) == 1)
    {
        count++;
        setCursor(23 + count, 4);        
        printf("" PURPLE "|" RESET CYAN " %-3d " RESET PURPLE "|" RESET " %-11lld " PURPLE "|" RESET " %-8s " PURPLE "|" RESET " %-30s " PURPLE "|" RESET BOLD " %-13s " RESET PURPLE "|" RESET " %-20s " PURPLE "|" RESET " %-9s " PURPLE "|" RESET "\n",
                count,
                employee.employeeID,
                employee.CIN_EM,
                employee.fullName,
                employee.E_phone_number,
                employee.E_adresse,
                employee.isAdmin ? GREEN BOLD "  Admin  " RESET :  " Regular " );
    }

    fclose(file);

    // Check if no employees were found
    if (count == 0) // file opened but no clients found
    {
        setCursor(24, 4);
        printf(PURPLE "|                                                                                                                          |\n" RESET);
        printf(PURPLE "|" RESET ORANGE "                                        No employees found in the database                                                  " RESET PURPLE "|\n" RESET);
        printf(PURPLE "|                                                                                                                          |\n" RESET);
        printf(PURPLE "+------------------------------------------------------------------------------------------------------------------+\n" RESET);
    }
    // if (count == 0)
    // {
    //     setCursor(24, 4);
    //     printf(ORANGE "No employees found in the database.\nIf you think there might be an issue, please report it to the technical team.\n" RESET);
    // }
    else
    {
        setCursor(24 + count, 4);
        printf(PURPLE "+------------------------------------------------------------------------------------------------------------------+\n" RESET);
        printf(GREEN "\nDisplayed" RESET BOLD " %d " RESET GREEN "employee(s) successfully.\n" RESET, count);
    }
}


