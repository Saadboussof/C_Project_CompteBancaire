#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char nom[20];
    int age;
} etudiant;

int main() {
    FILE *P;
    P = fopen("informations.bin", "rb");
    if (P == NULL) {
        printf("File open error.\n");
        exit(1);
    }

    // etudiant e1 = {"saad", 20};
    // etudiant e2 = {"boss", 22};

    // fwrite(&e1, sizeof(etudiant), 1, P);
    // fwrite(&e2, sizeof(etudiant), 1, P);

    etudiant e;

    while (fread(&e, sizeof(etudiant), 1, P)) {
        printf("Nom: %s, Age: %d\n", e.nom , e.age );
    }

    fclose(P);

    return 0;
}
