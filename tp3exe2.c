#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *fic;
    char strings[5][4]; 
    fic = fopen("informaton.txt", "w");
    if (fic == NULL) {
        printf("Ouverture du fichier impossible !\n");
        exit(1);
    }
    printf("Entrez 5 chaines de 3 caracteres chacune:\n");
    for (int i = 0; i < 5; i++) {
        printf("Chaine %d: ", i + 1);
        scanf("%3s", strings[i]); 
        fprintf(fic, "%s\n", strings[i]); 
    }
    fclose(fic);
    fic = fopen("informaton.txt", "a+");
    if (fic == NULL) {
        printf("Ouverture du fichier impossible !\n");
        exit(1);
    }
    printf("\nContenu du fichier:\n");
    char buffer[4];  
    rewind(fic);   
    while (fgets(buffer, sizeof(buffer), fic) != NULL) {
        printf("%s", buffer);
    }
    char b[4], c[4];
    int found = 0;
    printf("\nEntrez une chaine a rechercher (3 caracteres): ");
    scanf("%3s", b);
    rewind(fic);
    while ( fscanf(fic, "%3s", c) != EOF ) {
        if ( strcmp(c, b) == 0 ) {
            found = 1 ;
            break;  
        }
    }
    if (found) {
        printf("La chaine '%s' existe dans le fichier.\n", b);
    } else {
        printf("La chaine '%s' n'existe pas dans le fichier.\n", b);
    }
    fclose(fic);

    return 0;
}