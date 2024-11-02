#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[20];
    char prenom[20];
    int matr;
    float moy;
} etudiant;
void ajouter(char* nomfich, int n) {
    FILE *fich = fopen(nomfich, "ab+");  // Open in append mode "a" to add new students
    if (fich == NULL) {
        printf("Erreur lors de la creation du fichier.\n");
        exit(1);
    }
    printf(" ajoutee ici : \n");
    etudiant *etudiants = (etudiant *)malloc(n * sizeof(etudiant));
    for (int i = 0; i < n; i++) {
       printf(" le nom : ");
       scanf("%s", etudiants[i].nom);
       printf(" le prenom : ");
       scanf("%s", etudiants[i].prenom);
       printf(" matricule : ");
       scanf("%d", &etudiants[i].matr);
       printf(" la moyenne : ");
       scanf("%f", &etudiants[i].moy);
    }
    fwrite(etudiants, sizeof(etudiant), n, fich);
    free(etudiants);
    fclose(fich);
}
void afficha(char* nomfich) {
    FILE *fich = fopen(nomfich, "rb");
    if (fich == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    etudiant etud;
    printf("Liste des etudiants:\n");
    while (fread(&etud, sizeof(etudiant), 1, fich) == 1) {  // Read one student at a time
        printf("%s, %s, %d, %.2f\n", etud.nom, etud.prenom, etud.matr, etud.moy);
    }
    fclose(fich);
}
void rs(char* nomfich ) {
    FILE *fic = fopen(nomfich, "rb");
    if (fic == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    etudiant etu;
    char nom[20];
    printf("Entrez le nom de l'etudiant a rechercher: ");
    scanf("%s", nom);
    int found = 0;
    while (fread(&etu, sizeof(etudiant), 1, fic) == 1) {
        if ( strcmp(etu.nom, nom) == 0 ) {
            printf(" Etudiant trouve ! Moyenne: %.2f\n", etu.moy);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Etudiant non trouve.\n");
    }
    fclose(fic);
}

int main() {
    char s[30];
    int n;
   
    printf("Saisir le nom du fichier : ");
    scanf("%s", s);
    afficha(s);
    printf("Combien d'etudiants voulez-vous ajouter ? ");
    scanf("%d", &n);
    ajouter(s,n);
    afficha(s);
    rs(s);
    return 0;

}
