#ifndef USER_H
#define USER_H

typedef struct {
    char username[50];
    char password[50];
} User;

int signUp(User *user);
int logIn(User *user);

#endif 