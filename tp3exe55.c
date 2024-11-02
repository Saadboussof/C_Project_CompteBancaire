#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matr;
    char nom[20];
    char prenom[20];
    float moy;
} Etudiant;

void creerFichier() {
    FILE *fic = fopen("ETUDIANT.DAT", "wb");
    if (fic == NULL) {
        printf("Erreur lors de la création du fichier.\n");
        exit(1);
    }
    Etudiant etudiants[3] = {
        {1, "Martin", "Dupont", 14.5},
        {2, "Sophie", "Durand", 16.2},
        {3, "Jean", "Moreau", 12.9}
    };
    fwrite(etudiants, sizeof(Etudiant), 3, fic);
    printf("Fichier cree et initialisé avec 3 étudiants.\n");

    fclose(fic);
}


void afficherFichier() {
    FILE *fic = fopen("ETUDIANT.DAT", "rb");
    if (fic == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    Etudiant etu;
    printf("Liste des étudiants :\n");
    while (fread(&etu, sizeof(Etudiant), 1, fic)) {
        printf("Matricule: %d, Nom: %s, Prenom: %s, Moyenne: %.2f\n",
               etu.matr, etu.nom, etu.prenom, etu.moy);
    }
    fclose(fic);
}

void ajouterEtudiant() {
    FILE *fic = fopen("ETUDIANT.DAT", "ab");
    if (fic == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    Etudiant etu;
    printf("Entrez le matricule: ");
    scanf("%d", &etu.matr);
    printf("Entrez le nom: ");
    scanf("%s", etu.nom);
    printf("Entrez le prénom: ");
    scanf("%s", etu.prenom);
    printf("Entrez la moyenne: ");
    scanf("%f", &etu.moy);
    
    fwrite(&etu, sizeof(Etudiant), 1, fic);
    fclose(fic);
}

void rechercheSequencielle() {
    FILE *fic = fopen("ETUDIANT.DAT", "rb");
    if (fic == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    Etudiant etu;
    char nom[20];
    printf("Entrez le nom de l'etudiant a rechercher: ");
    scanf("%s", nom);
    int found = 0;
    while (fread(&etu, sizeof(Etudiant), 1, fic)) {
        if (strcmp(etu.nom, nom) == 0) {
            printf("Etudiant trouvé! Moyenne: %.2f\n", etu.moy);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Etudiant non trouve.\n");
    }
    fclose(fic);
}

void rechercheDirecte() {
    FILE *fic = fopen("ETUDIANT.DAT", "rb");
    if (fic == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    int position;
    printf("Entrez le numero de l'etudiant (commence a 0) : ");
    scanf("%d", &position);
    fseek(fic, position * sizeof(Etudiant) , SEEK_SET );
    Etudiant etu;
    if (fread(&etu, sizeof(Etudiant), 1, fic)) {
        printf("Matricule: %d, Nom: %s, Prenom: %s, Moyenne: %.2f\n",
               etu.matr, etu.nom, etu.prenom, etu.moy);
    } else {
        printf("Aucun étudiant trouvé à cet emplacement.\n");
    }
    fclose(fic);
}

void modifierMoyenne() {
    FILE *fic = fopen("ETUDIANT.DAT", "rb+");
    if (fic == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    int position;
    float nouvelleMoyenne;
    printf("Entrez le numero de l'etudiant a modifier: ");
    scanf("%d", &position);
    printf("Entrez la nouvelle moyenne: ");
    scanf("%f", &nouvelleMoyenne);
    
    fseek(fic, position * sizeof(Etudiant), SEEK_SET);
    Etudiant etu;
    if (fread(&etu, sizeof(Etudiant), 1, fic)) {
        etu.moy = nouvelleMoyenne;
        fseek(fic, position * sizeof(Etudiant), SEEK_SET);
        fwrite(&etu, sizeof(Etudiant), 1, fic);
        printf("Moyenne modifiee avec succes.\n");
    } else {
        printf("Aucun etudiant trouve a cet emplacement.\n");
    }
    fclose(fic);
}

int main() {
    int choix;
    do {
        printf("\nMenu:\n");
        printf("1. Creer le fichier\n");
        printf("2. Afficher les etudiants\n");
        printf("3. Recherche sequentielle\n");
        printf("4. Recherche directe\n");
        printf("5. Ajouter un etudiant\n");
        printf("6. Modifier la moyenne\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creerFichier();
                break;
            case 2:
                afficherFichier();
                break;
            case 3:
                rechercheSequencielle();
                break;
            case 4:
                rechercheDirecte();
                break;
            case 5:
                ajouterEtudiant();
                break;
            case 6:
                modifierMoyenne();
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}