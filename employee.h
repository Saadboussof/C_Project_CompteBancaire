<<<<<<< HEAD
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "tools.h"

// Define the Employee structure
typedef struct
{
    char fullName[100];
    char CIN_EM[9];
    char password[20];
    long long employeeID;
    char E_phone_number[11];
    char E_adresse[50];
    int isAdmin; // 1 for admin, 0 for regular employee
} Employee;

void logIn_Employee();
Employee createEmployee();
void Employee_Portal();
Employee *findEmployee(char *CIN, long long employeeID, int searchByCIN);
void signUpRequest_Employee(Employee *loggedInEmployee);
void saveEmployeeToFile(Employee *employee);
void Employee_Interface(Employee *loggedInEmployee);
void updateEmployeeDetails(Employee *loggedInEmployee);
// void manageClients();
// void approveRejectClient();
// void viewClientRequests();
void displayAllClients();
void displayEmployeeDetails(Employee *employee);
void processClientRequest();
void displayAllEmployees(Employee *loggedInEmployee);


#endif
=======
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "tools.h"

// Define the Employee structure
typedef struct
{
    char fullName[100];
    char CIN_EM[9];
    char password[20];
    long long employeeID;
    char E_phone_number[11];
    char E_adresse[50];
    int isAdmin; // 1 for admin, 0 for regular employee
} Employee;

void logIn_Employee();
Employee createEmployee();
void Employee_Portal();
Employee *findEmployee(char *CIN, long long employeeID, int searchByCIN);
void signUpRequest_Employee(Employee *loggedInEmployee);
void saveEmployeeToFile(Employee *employee);
void Employee_Interface(Employee *loggedInEmployee);
void updateEmployeeDetails(Employee *loggedInEmployee);
// void manageClients();
// void approveRejectClient();
// void viewClientRequests();
void displayAllClients();
void displayEmployeeDetails(Employee *employee);
void processClientRequest();
void displayAllEmployees(Employee *loggedInEmployee);


#endif
>>>>>>> 37ffb8eb5eaa8de37f6f1e7bdde6367bf5dd9583
