#ifndef CLIENT_H
#define CLIENT_H

#include "tools.h"

#define attemptCount_LIMIT 3 // for the "authenticateClient" function
typedef struct
{
    long long clientID;
    char CIN[9];
    char name[30];
    char phoneNumber[11];
    char address[50];
    char PIN[5];
    int activation;  // 0 - Inactive, 1 - Active
    int Blacklisted; // 0 - NO, 1 - Yes
    char dateCreated[23];

} Client;

void Client_Portal();
void requestCIN();
int isValidCIN(char *cin);
void logIn_Client();
int authenticateClient(Client *client);
int checkClientApprovalStatus(Client *client);
void signUpRequest();
Client createClient();
void updateClient(char *cin);
void saveClientToFile(Client *client);
Client *findClient(char *CIN, long long clientID, int searchByCIN);
void processClientRequest();
void reviewAccountUpdateRequest();
void displayClientDetails(Client *client);
void displayAllClients();
void displayFilteredClients(int filterType, int filterValue);
void viewProcedInactive();

#endif // CLIENT_H
