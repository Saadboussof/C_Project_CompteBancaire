<<<<<<< HEAD
#include "employee.h"



Employee *loggedInEmployee; // Global pointer for logged-in employee


char CIN_EM[9] = {'\0'};

void logIn_Employee()
{
    char CIN_EM[9];
    char password[20];
    int cinAttempts = 3;  // Maximum attempts allowed for CIN
    int passwordAttempts = 3; // Maximum attempts allowed for password

    Employee *employee = NULL;

    // CIN validation loop
    while (cinAttempts > 0)
    {
        printf("Enter your CIN: ");
        scanf(" %s", CIN_EM);
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



Employee createEmployee()
{
    Employee newEmployee;
    int isValid = 0;

    printf(BLUE "Creating a new employee...\n" RESET);

    // Get full name
    printf("Enter Employee Full Name: ");
    scanf(" %[^\n]", newEmployee.fullName);

    // // Get CIN
    // while (!isValid)
    // {
    //     printf("Enter Employee CIN: ");
    //     scanf(" %[^\n]", newEmployee.CIN_EM);
    //     isValid = isValidCIN(newEmployee.CIN_EM); // Reuse client CIN validation logic
    //     if (!isValid)
    //         printf(RED "Invalid CIN. Please try again.\n" RESET);
    // }
    // isValid = 0;

    strcpy(newEmployee.CIN_EM, CIN_EM);
    // printf("Employee CIN: %s",newEmployee.CIN_EM);
    // Get password
    // printf("Enter Employee Password: ");
    setAndConfirmPIN(newEmployee.password);

    // Assign employee ID
    newEmployee.employeeID = generateRandomAccountNumber();
    printf("Generated Employee ID: %lld\n", newEmployee.employeeID);

    // Get phone number
    while (!isValid)
    {
        printf("Enter Employee Phone Number (10 digits): ");
        scanf(" %[^\n]", newEmployee.E_phone_number);
        isValid = isNumericString(newEmployee.E_phone_number); // Validate phone number
        if (!isValid)
            printf(RED "Invalid phone number. Please enter a valid 10-digit phone number.\n" RESET);
    }
    isValid = 0;

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
        printf("why");
        return;
    }

    // if (strcmp(CIN_EM, "\0") == 0)
    // {
    printf("Enter the CIN for the new employee: ");
    scanf(" %s", CIN_EM);
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




void Employee_Interface(Employee *loggedInEmployee)
{
    char *Choices[] = {
        "Update Employee Details",
        "Approve/Reject Client Accounts",
        "Display All Clients",
        "Display All Employees",
        "Create Employee",
        "Log Out",   // Return to the previous menu or logout
        NULL};

    int choice;

    do
    {
        choice = choose_item(Choices, "Employee Interface: Choose an action");

        switch (choice)
        {
        case 0: // View Client Requests
            // printf("1");
            updateEmployeeDetails(loggedInEmployee);
            break;

        case 1: // Approve/Reject Client Accounts
            // printf("2");
            processClientRequest();
            break;

        case 2: // Manage Clients
            // printf("3");
            // manageClients();
            displayAllClients();
            break;
        case 3: // Manage Clients
            // printf("3");
            // manageClients();
            displayAllEmployees(loggedInEmployee);
            break;    

        case 4: // Change Password
            // printf("4");
            // changeEmployeePassword(loggedInEmployee);
            signUpRequest_Employee(loggedInEmployee);
            break;

        case 5: // Log Out
            printf("\nLogging out...\n");
            free(loggedInEmployee); // Free memory
            loggedInEmployee = NULL; // Reset the global pointer
            main();

        default: // Invalid option
            printf(RED "Invalid option. Please try again.\n" RESET);
        }

    } while (1);
=======
#include "employee.h"



Employee *loggedInEmployee; // Global pointer for logged-in employee


char CIN_EM[9] = {'\0'};

void logIn_Employee()
{
    char CIN_EM[9];
    char password[20];
    int cinAttempts = 3;  // Maximum attempts allowed for CIN
    int passwordAttempts = 3; // Maximum attempts allowed for password

    Employee *employee = NULL;

    // CIN validation loop
    while (cinAttempts > 0)
    {
        printf("Enter your CIN: ");
        scanf(" %s", CIN_EM);
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



Employee createEmployee()
{
    Employee newEmployee;
    int isValid = 0;

    printf(BLUE "Creating a new employee...\n" RESET);

    // Get full name
    printf("Enter Employee Full Name: ");
    scanf(" %[^\n]", newEmployee.fullName);

    // // Get CIN
    // while (!isValid)
    // {
    //     printf("Enter Employee CIN: ");
    //     scanf(" %[^\n]", newEmployee.CIN_EM);
    //     isValid = isValidCIN(newEmployee.CIN_EM); // Reuse client CIN validation logic
    //     if (!isValid)
    //         printf(RED "Invalid CIN. Please try again.\n" RESET);
    // }
    // isValid = 0;

    strcpy(newEmployee.CIN_EM, CIN_EM);
    // printf("Employee CIN: %s",newEmployee.CIN_EM);
    // Get password
    // printf("Enter Employee Password: ");
    setAndConfirmPIN(newEmployee.password);

    // Assign employee ID
    newEmployee.employeeID = generateRandomAccountNumber();
    printf("Generated Employee ID: %lld\n", newEmployee.employeeID);

    // Get phone number
    while (!isValid)
    {
        printf("Enter Employee Phone Number (10 digits): ");
        scanf(" %[^\n]", newEmployee.E_phone_number);
        isValid = isNumericString(newEmployee.E_phone_number); // Validate phone number
        if (!isValid)
            printf(RED "Invalid phone number. Please enter a valid 10-digit phone number.\n" RESET);
    }
    isValid = 0;

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
        printf("why");
        return;
    }

    // if (strcmp(CIN_EM, "\0") == 0)
    // {
    printf("Enter the CIN for the new employee: ");
    scanf(" %s", CIN_EM);
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




void Employee_Interface(Employee *loggedInEmployee)
{
    char *Choices[] = {
        "Update Employee Details",
        "Approve/Reject Client Accounts",
        "Display All Clients",
        "Display All Employees",
        "Create Employee",
        "Log Out",   // Return to the previous menu or logout
        NULL};

    int choice;

    do
    {
        choice = choose_item(Choices, "Employee Interface: Choose an action");

        switch (choice)
        {
        case 0: // View Client Requests
            // printf("1");
            updateEmployeeDetails(loggedInEmployee);
            break;

        case 1: // Approve/Reject Client Accounts
            // printf("2");
            processClientRequest();
            break;

        case 2: // Manage Clients
            // printf("3");
            // manageClients();
            displayAllClients();
            break;
        case 3: // Manage Clients
            // printf("3");
            // manageClients();
            displayAllEmployees(loggedInEmployee);
            break;    

        case 4: // Change Password
            // printf("4");
            // changeEmployeePassword(loggedInEmployee);
            signUpRequest_Employee(loggedInEmployee);
            break;

        case 5: // Log Out
            printf("\nLogging out...\n");
            free(loggedInEmployee); // Free memory
            loggedInEmployee = NULL; // Reset the global pointer
            main();

        default: // Invalid option
            printf(RED "Invalid option. Please try again.\n" RESET);
        }

    } while (1);
>>>>>>> 37ffb8eb5eaa8de37f6f1e7bdde6367bf5dd9583
}