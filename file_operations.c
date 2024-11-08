#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"

/*
int convertBinaryToText(const char *binaryFileName, const char *textFileName)
{
  FILE *binaryFile, *textFile;

  binaryFile = fopen(binaryFileName, "rb");
  if (binaryFile == NULL)
  {
    perror("Error opening binary file");
    return -1;
  }

  textFile = fopen(textFileName, "w");
  if (textFile == NULL)
  {
    perror("Error opening text file");
    fclose(binaryFile);
    return -1;
  }

  unsigned char byte;
  while (fread(&byte, sizeof(byte), 1, binaryFile) == 1)
  {
    if (isprint(byte)) // Check if byte is a printable character
      fputc(byte, textFile);
    else
      fputc('.', textFile); // Replace non-printable characters with '.'
  }

  fclose(binaryFile);
  fclose(textFile);

  printf("Your text file is ready and named as %s.\n", textFileName);
  return 0;
}
*/




void loadAccountsFromFile()
{

    FILE *file = fopen("accounts.dat", "rb");

    if (file == NULL)
    {
        printf("No accounts found or failed to open file.\n");
        return;
    }

    printf("\n------------------- Accounts -------------------\n");

    Account account;
    while (fread(&account, sizeof(Account), 1, file) == 1)
    {
        printf("Account ID: %lld\nOwner ID: %lld\nBalance: %.2f\nType of account: %s\n", account.accountID, account.ownerID, account.balance, account.accountType);
    }

    fclose(file);
}

void loadClientsFromFile()
{

    FILE *file = fopen("clients.dat", "rb");

    if (file == NULL)
    {
        printf("No clients found or failed to open file.\n");
        return;
    }

    printf("\n------------------- Clients -------------------\n");

    Client client;
    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
        printf("Client ID: %lld\nName: %s\nCIN: %s\nPhone Number: %s\naddress: %s\n", client.clientID, client.name, client.CIN, client.phoneNumber, client.address);
    }

    fclose(file);
}


