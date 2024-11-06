#ifndef CLIENT_H
#define CLIENT_H

typedef struct
{
//  -------------------------------- 1.Identification Fields --------------------------------
    long long clientID;
    char CIN[9];
//  -------------------------------- 2.Personal Information ---------------------------------
    char name[150];             
    char phoneNumber[11];
    char address[100];
//  -------------------------------- 4.client Status ----------------------------------------    
    int isBlacklisted;
//  -------------------------------- 5.Metadata ---------------------------------------------
    char dateCreated[23];
} Client;


int createClient();

#endif // CLIENT_H
