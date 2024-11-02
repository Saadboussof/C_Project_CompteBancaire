#include <stdio.h>
typedef struct {
    int numerateur;
    int denominateur; 
} NombreRationnel;
void saisirRationnel(NombreRationnel *r) {
    printf("Entrez le numerateur: ");
    scanf("%d", &r->numerateur);
    printf("Entrez le denominateur: ");
    scanf("%d", &r->denominateur);
}
void afficherRationnel(NombreRationnel r) {
    printf("%d/%d\n", r.numerateur, r.denominateur);
}
NombreRationnel additionRationnels(NombreRationnel r1, NombreRationnel r2) {
    NombreRationnel resultat;
    resultat.numerateur = r1.numerateur * r2.denominateur + r2.numerateur * r1.denominateur;
    resultat.denominateur = r1.denominateur * r2.denominateur;
    return resultat;
}
NombreRationnel multiplicationRationnels(NombreRationnel r1, NombreRationnel r2) {
    NombreRationnel resultat;
    resultat.numerateur = r1.numerateur * r2.numerateur;
    resultat.denominateur = r1.denominateur * r2.denominateur;
    return resultat;
}

int main() {
    NombreRationnel r1, r2, somme, produit;
    printf("Saisir le premier nombre rationnel:\n");
    saisirRationnel(&r1);
    printf("Saisir le deuxieme nombre rationnel:\n");
    saisirRationnel(&r2);
    printf("Premier nombre rationnel: ");
    afficherRationnel(r1);
    printf("Deuxieme nombre rationnel: ");
    afficherRationnel(r2);
    somme = additionRationnels(r1, r2);
    printf("Somme: ");
    afficherRationnel(somme);
    produit = multiplicationRationnels(r1, r2);
    printf("Produit: ");
    afficherRationnel(produit);

    return 0;
}
