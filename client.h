#ifndef CLIENT_H
#define CLIENT_H

typedef struct
{
    long long clientID;
    char CIN[9];
    char name[150];
    char phoneNumber[11];
    char address[100];
    char PIN[5];
    int activation;        // 0 - Inactive, 1 - Active
    int Blacklisted;         // 0 - NO, 1 - Yes  
    char dateCreated[23];
    
} Client;

void Client_Portal();
void logIn_Client();
void signUpRequest();
void requestCIN();
void authenticateClient(Client *client);
Client *findClientByCIN(char *CIN);
int checkClientApprovalStatus(Client *client);
void createClient();
void saveRequestToFile(Client *client);
void processClientRequest();
void saveClientToFile(Client *client);
void displayClientDetails(Client *client);
void displayAllClients();

#endif // CLIENT_H
