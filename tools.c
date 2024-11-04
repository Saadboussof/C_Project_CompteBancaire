#include <time.h>

#define ACCOUNT_NUMBER_MIN 0
#define ACCOUNT_NUMBER_MAX 9999999999

long long generateRandomAccountNumber()
{
  return ACCOUNT_NUMBER_MIN + (rand() % (ACCOUNT_NUMBER_MAX + 1 - ACCOUNT_NUMBER_MIN));
}

void getCurrentDate(char *buffer, size_t bufferSize)
{
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(buffer, bufferSize, "%Y-%m-%d at %H:%M:%S", t);
}