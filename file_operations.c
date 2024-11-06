#include <stdio.h>
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

int saveClientToFile(Client *client)
{
  FILE *file = fopen("clients.dat", "ab");

  if (file == NULL)
  {
    printf("Failed to open file for saving client.\n");
    return -1;
  }

  fwrite(client, sizeof(Client), 1, file);

  fclose(file);

  printf("Client saved successfully!\n");

  return 0;
}

Client *findClientByCIN(const char *CIN)
{
  static Client client; // Static so it persists outside the function
  FILE *file = fopen("clients.dat", "rb");

  if (file == NULL)
  {
    printf("No clients found or failed to open file.\n");
    return NULL;
  }

  while (fread(&client, sizeof(Client), 1, file) == 1)
  {
    if (strcmp(client.CIN, CIN) == 0)
    {
      fclose(file);
      return &client;
    }
  }

  fclose(file);
  return NULL;
}

int saveAccountToFile(Account *account)
{
  FILE *file = fopen("accounts.dat", "ab");

  if (file == NULL)
  {
    printf("Failed to open file for saving account.\n");
    return -1;
  }

  fwrite(account, sizeof(Account), 1, file);

  fclose(file);

  printf("Account saved successfully!\n");

  return 0;
}

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

void deleteAccountFromFile(long long accountID)
{
  FILE *file = fopen("accounts.dat", "rb");
  FILE *tempFile = fopen("temp.dat", "wb");

  if (file == NULL || tempFile == NULL)
  {
    printf("Error opening files for deletion.\n");
    if (file)
      fclose(file);
    if (tempFile)
      fclose(tempFile);
    return;
  }

  Account account;
  int found = 0;

  while (fread(&account, sizeof(Account), 1, file) == 1)
  {
    if (account.accountID != accountID)
    {
      fwrite(&account, sizeof(Account), 1, tempFile);
    }
    else
    {
      found = 1; // Without break so we'll make sure all accounts are copied
    }
  }

  fclose(file);
  fclose(tempFile);

  if (found)
  {
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");
    printf("Account deleted successfully.\n");
  }
  else
  {
    remove("temp.dat");
    printf("Account not found.\n");
  }
}
