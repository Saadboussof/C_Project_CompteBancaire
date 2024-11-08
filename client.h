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
    int isBlacklisted;
    char dateCreated[23];
    // int role;   to add employees
} Client;

void logIn_Client();
void signUp();
Client *findClientByCIN(char *CIN);
void authenticateClient(Client *client);
void requestCIN();
void createClient();
void saveClientToFile(Client *client);
void displayClientDetails(Client *client);

#endif // CLIENT_H
