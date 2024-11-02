#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nom[15], prenom[15];
    int CNE;
    float notes[4], moyenne;
} etudiant;

etudiant lit() {
    etudiant t;
    printf("Entrez le nom et le prenom: ");
    scanf("%s%s", t.nom, t.prenom);
    printf("Entrez le CNE: ");
    scanf("%d", &t.CNE);
    t.moyenne = 0;
    for (int i = 0; i < 4; i++) {
        printf("Entrez la note %d: ", i + 1);
        scanf("%f", &t.notes[i]);
        t.moyenne += t.notes[i];
    }
    t.moyenne /= 4;
    return t;
}
void trier_etudiants_par_moyenne(etudiant etu[], int n) {
    etudiant temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (etu[i].moyenne < etu[j].moyenne) {
                temp = etu[i];
                etu[i] = etu[j];
                etu[j] = temp;
            }
        }
    }
}
void affichage ( etudiant t ){
    printf(" le nome : %s ",t.nom);
    printf(" le prenom : %s ",t.prenom);
    printf(" le CNE : %d ",t.CNE);
    printf(" le moyenne : %.2f ",t.moyenne);
}
int main() {
    int n;
    float moyenne_generale = 0;

    printf("Veuillez donner le nombre d'etudiants: ");
    scanf("%d", &n);
    etudiant etu[n];
    for (int i = 0; i < n; i++) {
        etu[i] = lit();
        moyenne_generale += etu[i].moyenne;
    }
    moyenne_generale /= n;
    printf("La moyenne generale est: %.2f\n", moyenne_generale);
    float max = etu[0].moyenne ;
    for(int i = 1 ; i < n ; i++ ){
     if (etu[0].moyenne < etu[i].moyenne){
        max = etu[i].moyenne ;
     }
    }
    printf(" le moyen plus grand est : %.2f ",max);
    printf("\n l'order decroissant selon les moyennes :\n");
    trier_etudiants_par_moyenne( etu , n );
     for (int i = 0; i < n; i++) {
        printf(" %.2f3 \n",etu[i].moyenne);
    }
    
    return 0;
}
