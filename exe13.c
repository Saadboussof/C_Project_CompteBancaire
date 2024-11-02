#include <stdio.h>
#include <stdlib.h>
typedef struct {
int jour ; char mois[10] ; int annee ;
}date ;
typedef struct {
 char nom[15] , prenom[15] ;
  date anniversire ;
  date date_embauche ;
}employe ;
employe lit( int n ){
 employe t ;
 for (int i = 0 ; i < n ; i++ ){
    printf(" votre nome : ");
    scanf("%s",t.nom);
    printf("\n votre prenom :");
    scanf("%s",t.prenom);
    printf(" \n date anniversire : ");
    scanf("%d%s%d",&t.anniversire.jour,&t.anniversire.mois,&t.anniversire.annee);
     printf(" \n date embauche : ");
    scanf("%d%s%d",&t.date_embauche.jour,&t.date_embauche.mois,&t.date_embauche.annee);
 }
 return t ;
}
void affichage ( employe t , int n ){
    for ( int i = 0 ; i < n ; i++ ){
    printf(" votre nome : %s ",t.nom);
    printf("\n votre prenom : %s ",t.prenom);
    printf(" \n date anniversire : %d / %s / %d ",t.anniversire.jour,t.anniversire.mois,t.anniversire.annee);
    printf(" \n date embauche : %d / %s / %d ",t.date_embauche.jour,t.date_embauche.mois,t.date_embauche.annee);
    }
}
int main() {
    int i ;
    int n = 1 ;
    employe employes[n] ;
    for ( i = 0 ; i < n ; i++ ){
       employes[i] = lit(n);
    }
   for ( i = 0 ; i < n ; i++ ){
       affichage(employes[i],n);
    }
 return 0 ;
}