#include "employee.h"



Employee *loggedInEmployee; // Global pointer for logged-in employee


char CIN_EM[9] = {'\0'};

void Employee_Portal()
{
    char *Choices[] = {
        "Log in",
        "Return",   // Return to the main menu
        "Exit",     // Exit the application
        NULL};

    int choice = choose_item(Choices, "Employee Portal: Make your choice");

    switch (choice)
    {
    case 0: // Log in
        logIn_Employee();
        break;
    // case 1: // Sign up
    //     signUpRequest_Employee(); // Sign-up logic for employees
    //     break;
    case 1: // Return
        main();
        break;
    default: // Exit
        exit(0);
        break;
    }
}

void logIn_Employee()
{
    char CIN_EM[9];
    char password[5];
    int cinAttempts = 3;  // Maximum attempts allowed for CIN
    int passwordAttempts = 3; // Maximum attempts allowed for password

    Employee *employee = NULL;

    // CIN validation loop
    while (cinAttempts > 0)
    {
        while (1)
    {
        printf("Enter your CIN: ");
        scanf(" %s", CIN_EM);

        // Validate CIN
        if (isValidCIN(CIN_EM))
            break;
        else
            printf(RED "Invalid CIN. Please try again.\n" RESET);
    }
        // printf("\n%s\n",CIN_EM);

        // Attempt to find the employee by CIN
        employee = findEmployee(CIN_EM, 0, 1);

        if (employee != NULL)
        {
            // CIN is valid, proceed to password verification
            break;
        }
        else
        {
            cinAttempts--;
            printf(RED "Employee with CIN: %s not found. You have %d attempt(s) remaining.\n" RESET, CIN_EM, cinAttempts);
        }
    }

    // If CIN attempts are exhausted
    if (cinAttempts == 0)
    {
        printf(RED "Too many incorrect CIN attempts. Returning to the login interface.\n" RESET);
        Employee_Portal(); // Return to the login interface
        return;
    }

    // Password validation loop
    while (passwordAttempts > 0)
    {
        printf("Enter Employee Password: ");
        PIN_hide(password, sizeof(password)); // Hide password input

        if (strcmp(employee->password, password) == 0)
        {
            // Successful login
            printf(GREEN "Login successful. Welcome, %s!\n" RESET, employee->fullName);
            loggedInEmployee = employee; // Set global variable for logged-in employee

            // Display employee details and provide options via interface
            displayEmployeeDetails(loggedInEmployee);
            Employee_Interface(loggedInEmployee); // Redirect to employee actions
            return; // Exit after successful login
        }
        else
        {
            passwordAttempts--;
            printf(RED "Incorrect password. You have %d attempt(s) remaining.\n" RESET, passwordAttempts);
        }
    }

    // If password attempts are exhausted
    if (passwordAttempts == 0)
    {
        printf(RED "Too many incorrect password attempts. Returning to the login interface.\n" RESET);
        free(employee); // Free allocated memory
        Employee_Portal(); // Return to the login interface
    }
}

void signUpRequest_Employee(Employee *loggedInEmployee)
{
    // Ensure a logged-in employee exists
    if (loggedInEmployee == NULL)
    {
        printf(RED "Access Denied: You must log in first.\n" RESET);
        return;
    }

    // Restrict access to admin employees only
    if (!loggedInEmployee->isAdmin)
    {
        printf(RED "Access Denied: Only admin employees can create new employees.\n" RESET);
        // printf("why");
        return;
    }

    // if (strcmp(CIN_EM, "\0") == 0)
    // {
    while (1)
    {
        printf("Enter your CIN of the new employee: ");
        scanf(" %s", CIN_EM);

        // Validate CIN
        if (isValidCIN(CIN_EM))
            break;
        else
            printf(RED "Invalid CIN. Please try again.\n" RESET);
    }
    // }

    // Check if the employee already exists
    Employee *existingEmployee = findEmployee(CIN_EM, 0, 1);
    if (existingEmployee != NULL)
    {
        printf(BLUE "Employee with CIN: %s already exists.\nRedirecting to login...\n" RESET, CIN_EM);
        free(existingEmployee); // Free allocated memory
        logIn_Employee();       // Redirect to login if employee exists
        return;
    }
    else
    {
        // Create and save a new employee
        Employee newEmployee = createEmployee();
        saveEmployeeToFile(&newEmployee);
        printf(GREEN "Employee successfully created and saved!\n" RESET);
        displayEmployeeDetails(&newEmployee);
    }
}


Employee createEmployee()
{
    Employee newEmployee;
    int isValid = 0;
    int check = false;

    printf(BLUE "Creating a new employee...\n" RESET);

    // Get full name
    while (!check)
    {
        printf("Enter employee Full Name: ");
        scanf(" %[^\n]", newEmployee.fullName);
        check = isAlphaString(newEmployee.fullName);
        if (!check)
            printf(RED "Invalide name please try again.\n" RESET);
    }
    check = false;

    

    strcpy(newEmployee.CIN_EM, CIN_EM);
    // Get password
    setAndConfirmPIN(newEmployee.password);

    // Assign employee ID
    newEmployee.employeeID = generateRandomAccountNumber();
    printf("Generated Employee ID: %lld\n", newEmployee.employeeID);

    // Get phone number
    while (!check)
    {
        printf("Enter Client Phone Number: ");
        scanf(" %[^\n]", newEmployee.E_phone_number);
        check = (isNumericString(newEmployee.E_phone_number) && (strlen(newEmployee.E_phone_number) == 10) && (newEmployee.E_phone_number[0] == '0'));
        if (!check)
            printf(RED "Invalide Phone Number please try again.\n" RESET);
    }
    check = false;

    // Get address
    printf("Enter Employee Address: ");
    scanf(" %[^\n]", newEmployee.E_adresse);

    // Admin privileges
    printf("Is this employee an admin? (1-Yes, 0-No): ");
    while (scanf("%d", &newEmployee.isAdmin) != 1 || (newEmployee.isAdmin != 0 && newEmployee.isAdmin != 1))
    {
        printf(RED "Invalid input. Please enter 1 for Yes or 0 for No: " RESET);
        while (getchar() != '\n'); // Clear invalid input
    }

    return newEmployee;
}


void Employee_Interface(Employee *loggedInEmployee)
{
    if (loggedInEmployee == NULL)
    {
        printf(RED "ERROR: Access Denied.\n" RESET);
        printf(YELLOW "You must be logged in to access this interface.\n" RESET);
        return;
    }

    // Menu choices for employee functionalities
    char *Choices[] = {
        "Clients Functionalities",
        "Employee functionalities",
        BLUE "Update Employee Details" RESET,
        "Log out", // Return to the main menu
        NULL};

    int choice;

    do
    {
        choice = choose_item(Choices, "Employee Interface");

        switch (choice)
        {
        case 0: // Update Employee Details
            Regular_Employee_Interface(loggedInEmployee);
            break;

        case 1: // Display All Clients
            Admin_Interface(loggedInEmployee);
            break;

        case 2: // Display All Employees
            updateEmployeeDetails(loggedInEmployee);
            break;

        case 3: // Log Out
            // printf("\nLogging out...\n");
            // No memory freeing if loggedInEmployee is managed globally
            // main(); // Return to main menu
            return;
        case 4: // Display All Employees
            // updateEmployeeDetails(loggedInEmployee);
            printf("\nExit Programe...\n");
            exit(0);
        default: // Invalid option
            printf(RED "Invalid option. Please try again.\n" RESET);
        }

    } while (1); // Keep the interface running until logout
}




void Admin_Interface(Employee *loggedInEmployee)
{
    if (loggedInEmployee == NULL)
    {
        printf(RED "ERROR: Access Denied.\n" RESET);
        printf(YELLOW "You must be logged in to access this interface.\n" RESET);
        return;
    }
    // Restrict access to admin employees only
    if (!loggedInEmployee->isAdmin)
    {
        printf(RED "Access Denied: Only admin employees can open this window.\n" RESET);
        // printf("why");
        return;
    }

    // Menu choices for employee functionalities
    char *Choices[] = {
        "Display All Employees",
        "Create Employee",
        "Delete Employee",
        "Return",
        "Exit", // Return to the main menu
        NULL};

    int choice;

    do
    {
        choice = choose_item(Choices, "Admin Interface");

        switch (choice)
        {
        case 0: // Update Employee Details
            displayAllEmployees(loggedInEmployee);
            break;

        case 1: // Display All Clients
            signUpRequest_Employee(loggedInEmployee);
            break;

        case 2: // Display All Employees
            deleteEmployee(loggedInEmployee);
            break;

        case 3: // Display All Employees
            // deleteEmployee(loggedInEmployee);
            return;

        case 4: // Log Out
            printf("\nExit Programe...\n");
            // No memory freeing if loggedInEmployee is managed globally
            // main(); // Return to main menu
            exit(0);

        default: // Invalid option
            printf(RED "Invalid option. Please try again.\n" RESET);
        }

    } while (1); // Keep the interface running until logout
}


void Regular_Employee_Interface(Employee *loggedInEmployee)
{
    char *Choices[] = {
        "Approve/Reject Clients",
        "Display All Clients",
        "Blocked/Activite account",
        "Delete Client",
        "Return",
        "Exit",   // Return to the previous menu or logout
        NULL};

    int choice;

    do
    {
        choice = choose_item(Choices, "Regular Employee Interface: ");

        switch (choice)
        {
        case 0: // View Client Requests
            // printf("1");
            processClientRequest();
            break;

        case 1: // Approve/Reject Client Accounts
            // printf("2");
            displayAllClients();
            break;
        case 2: // return 
            toggleAccountStatusByID(loggedInEmployee);      
            return;  

        case 3: // return  
            deleteClientByID(loggedInEmployee);        
            return;

        case 4: // return          
            return;    

        case 5: // Exit
            printf("\nExit Program...\n");
            free(loggedInEmployee); // Free memory
            loggedInEmployee = NULL; // Reset the global pointer
            exit(0);

        default: // Invalid option
            printf(RED "Invalid option. Please try again.\n" RESET);
        }

    } while (1);
}










