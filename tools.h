#ifndef TOOLS_H
#define TOOLS_H

long long generateRandomAccountNumber();
void getCurrentDate(char *buffer, size_t bufferSize);
int choose_item(char **items, const char *title);
void PIN_hide(char *PIN, int max_length);
int validatePIN(const char *enteredPIN, const char *correctPIN);

#endif // TOOLS_H