<<<<<<< HEAD
#include "employee.h"

 Employee *findEmployee(char *CIN, long long employeeID, int searchByCIN) // 0- ID   1- CIN
{
    FILE *file = fopen("employees.dat", "ab+");
    if (file == NULL)
    {
        printf(RED "ERROR: Failed to open employees file\n" RESET);
        printf(RED "We're sorry, but we encountered a technical issue while accessing employee data. Please try again later or contact support.\n" RESET);
        exit(EXIT_FAILURE); // Exit program if file cannot be opened
    }

    Employee *employee = malloc(sizeof(Employee));
    if (employee == NULL)
    {
        printf(RED "ERROR: Failed to allocate memory\n" RESET);
        fclose(file);
        exit(EXIT_FAILURE); // Exit program if memory allocation fails
    }
    // printf("hhhhhhhhhhhhhhhh\n");

    while (fread(employee, sizeof(Employee), 1, file) == 1)
    {
        // printf("Checking CIN in file: %s\n", CIN);
        // Search by CIN
        if (searchByCIN && strcmp(employee->CIN_EM, CIN) == 0)
        {
            // printf("vbn");
            fclose(file);
            return employee; // Return employee if CIN matches
        }
        // Search by employeeID
        else if (!searchByCIN && employee->employeeID == employeeID)
        {
            // printf("vbnfgh");
            fclose(file);
            return employee; // Return employee if employeeID matches
        }
    }

    free(employee); // Free memory if no match is found
    fclose(file);
    return NULL; // Return NULL if employee not found
}

// // void signUpRequest_Employee()
// {
// }

void saveEmployeeToFile(Employee *employee)
{
    FILE *file = fopen("employees.dat", "ab"); // Open file in append mode (binary)
    if (file == NULL)
    {
        printf(RED "Error saving employee data.\n" RESET);
        return;
    }
    fwrite(employee, sizeof(Employee), 1, file); // Write the employee struct to file
    fclose(file);
    printf(GREEN "Employee saved successfully!\n" RESET);
=======
#include "employee.h"

 Employee *findEmployee(char *CIN, long long employeeID, int searchByCIN) // 0- ID   1- CIN
{
    FILE *file = fopen("employees.dat", "ab+");
    if (file == NULL)
    {
        printf(RED "ERROR: Failed to open employees file\n" RESET);
        printf(RED "We're sorry, but we encountered a technical issue while accessing employee data. Please try again later or contact support.\n" RESET);
        exit(EXIT_FAILURE); // Exit program if file cannot be opened
    }

    Employee *employee = malloc(sizeof(Employee));
    if (employee == NULL)
    {
        printf(RED "ERROR: Failed to allocate memory\n" RESET);
        fclose(file);
        exit(EXIT_FAILURE); // Exit program if memory allocation fails
    }
    // printf("hhhhhhhhhhhhhhhh\n");

    while (fread(employee, sizeof(Employee), 1, file) == 1)
    {
        // printf("Checking CIN in file: %s\n", CIN);
        // Search by CIN
        if (searchByCIN && strcmp(employee->CIN_EM, CIN) == 0)
        {
            // printf("vbn");
            fclose(file);
            return employee; // Return employee if CIN matches
        }
        // Search by employeeID
        else if (!searchByCIN && employee->employeeID == employeeID)
        {
            // printf("vbnfgh");
            fclose(file);
            return employee; // Return employee if employeeID matches
        }
    }

    free(employee); // Free memory if no match is found
    fclose(file);
    return NULL; // Return NULL if employee not found
}

// // void signUpRequest_Employee()
// {
// }

void saveEmployeeToFile(Employee *employee)
{
    FILE *file = fopen("employees.dat", "ab"); // Open file in append mode (binary)
    if (file == NULL)
    {
        printf(RED "Error saving employee data.\n" RESET);
        return;
    }
    fwrite(employee, sizeof(Employee), 1, file); // Write the employee struct to file
    fclose(file);
    printf(GREEN "Employee saved successfully!\n" RESET);
>>>>>>> 37ffb8eb5eaa8de37f6f1e7bdde6367bf5dd9583
}