#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "client.h"
#include "account.h"

// Define ANSI color codes for highlighting and style
#define CYAN "\033[0;36m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define RED "\033[31m"
#define MAGENTA "\033[35m"
#define ORANGE "\033[38;5;214m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"


void main();
long long generateRandomAccountNumber();
void getCurrentDate(char *buffer, size_t bufferSize);
int choose_item(char **items, char *title);
bool setAndConfirmPIN(char *PIN);
void PIN_hide(char *PIN, int max_length);
int validatePIN(const char *enteredPIN, const char *correctPIN);
int isAlphaString(char *str);
int isNumericString(char *str);
int isAlphanumericString(char *str);
void fordelay(int j);
void displaySpectacularLoadingBar(int duration);
void gradientSpinner(int duration);
void typingEffect(const char *text, int speed);
#endif // TOOLS_H