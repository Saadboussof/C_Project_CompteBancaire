#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[20];
    char prenom[20];
    int matr;
    float moy;
} etudiant;
int main() {
    FILE *fic;
    fic = fopen("etud.dat", "wb");
    if (fic == NULL) {
        printf("Ouverture du fichier impossible !\n");
        exit(1);
    }
    etudiant *etudiants = (etudiant *)malloc(3 * sizeof(etudiant)); //initialisatoin  
    if (etudiants == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(etudiants[0].nom, "saad");
    strcpy(etudiants[0].prenom, "boussof");
    etudiants[0].matr = 1;
    etudiants[0].moy = 12.2;

    strcpy(etudiants[1].nom, "abdo");
    strcpy(etudiants[1].prenom, "aze");
    etudiants[1].matr = 2;
    etudiants[1].moy = 19.9;

    strcpy(etudiants[2].nom, "wael");
    strcpy(etudiants[2].prenom, "chafoui");
    etudiants[2].matr = 3;
    etudiants[2].moy = 5.99;

    fwrite(etudiants, sizeof(etudiant), 3, fic);
    fclose(fic);
    free(etudiants);
    fic = fopen("etud.dat", "rb");
    if (fic == NULL) {
        printf("Ouverture du fichier impossible !\n");
        exit(1);
    }
    etudiant *etudiant1 = (etudiant *)malloc(3 * sizeof(etudiant));
    if (etudiant1 == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    fread(etudiant1, sizeof(etudiant), 3, fic);
    for (int i = 0; i < 3; i++) {
        printf("Nom: %s, Prenom: %s, Matricule: %d, Moyenne: %.2f\n", 
               etudiant1[i].nom, etudiant1[i].prenom, etudiant1[i].matr, etudiant1[i].moy);
    }
    fclose(fic);
    int ajout;
    printf("Combien des etudiants tu veux ajouter? : ");
    scanf("%d", &ajout);
    etudiant1 = (etudiant *)realloc(etudiant1, (3 + ajout) * sizeof(etudiant));
    if (etudiant1 == NULL) {
        printf("Memory reallocation failed!\n");
        exit(1);
    }
    for (int i = 3; i < 3 + ajout; i++) {
        printf("Enter details for student %d\n", i + 1);
        printf("Nom: ");
        scanf("%s", etudiant1[i].nom);
        printf("Prenom: ");
        scanf("%s", etudiant1[i].prenom);
        printf("Matricule: ");
        scanf("%d", &etudiant1[i].matr);
        printf("Moyenne: ");
        scanf("%f", &etudiant1[i].moy);
    }
    fwrite(etudiant1, sizeof(etudiant), 3, fic);
    printf("\n Updated student list :\n");
    for (int i = 0; i < 3 + ajout; i++) {
        printf("Nom: %s, Prenom: %s, Matricule: %d, Moyenne: %.2f\n", 
               etudiant1[i].nom, etudiant1[i].prenom, etudiant1[i].matr, etudiant1[i].moy);
    }
    fic = fopen("etud.dat", "a+");
    if (fic == NULL) {
        printf("Ouverture du fichier impossible !\n");
        exit(1);
    }
    int num ;
    float moy ;
    printf(" tu veux modifier la moyanne de qu'il etudiant ? : ");
    scanf("%d",&num);
    printf(" moy : ");
    scanf("%f",&moy);
    for (int i = 0; i < 3 + ajout; i++) {
        if (etudiant1[i].matr == num) {
            etudiant1[i].moy = moy;
            break;
        }
    }
    for (int i = 0; i < 3 + ajout; i++) {
        printf("Nom: %s, Prenom: %s, Matricule: %d, Moyenne: %.2f\n", 
               etudiant1[i].nom, etudiant1[i].prenom, etudiant1[i].matr, etudiant1[i].moy);
    }
    printf("\n");
    int z ;
    printf(" n eme etu : ");
    scanf("%d",&z);
    for (int i = 0; i < 3 + ajout; i++) {
        if( z == etudiant1[i].matr ){
        printf("Nom: %s, Prenom: %s, Matricule: %d, Moyenne: %.2f\n", 
               etudiant1[i].nom, etudiant1[i].prenom, etudiant1[i].matr, etudiant1[i].moy);
        break ;
        }
    }

     free(etudiant1);
     fclose(fic);
    char etu[10];
    printf(" donnee le nom de etudiant : ");
    scanf("%s",etu);
    for (int i = 0; i < 3 + ajout; i++) {
        if( strcmp(etu,etudiant1[i].nom) == 0 ){
        printf("Nom: %s, Prenom: %s, Matricule: %d, Moyenne: %.2f\n", 
               etudiant1[i].nom, etudiant1[i].prenom, etudiant1[i].matr, etudiant1[i].moy);
        break ;
        }
    }
    return 0;
}
