#include <stdio.h>
#include <string.h>
#include "user.h"

int signUp(User *user) {
    printf("Enter username: ");
    scanf("%s", user->username);
    printf("Enter password: ");
    scanf("%s", user->password);
    printf(" User signed up successfully! \n");
    return 0; 
}
int logIn(User *user) {
    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if ( strcmp(username, user->username) == 0 && strcmp(password, user->password) == 0) {
        printf(" Login successful! \n");
        return 1; 
    } else {
        printf(" Login failed! \n");
        return 0;
    }
}
