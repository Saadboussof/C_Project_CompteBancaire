#include <stdio.h>
#include <stdlib.h>
typedef struct {
  int nbele ;
  int *tab ;
} tableau;
tableau ctableau ( int n ){
    tableau t ;
    t.nbele = n ;
    t.tab = (int *)malloc( n * sizeof(int));
   return t ;
}
void ddd ( tableau t ){
    free(t.tab);
    
}
void slecture (tableau t ){

    for( int i = 0 ; i < t.nbele ; i++ ){
        printf("\n t(%d) = ",i+1);
        scanf("%d",&t.tab[i]);
    }
}
void afficharge ( tableau t ){

  for( int i = 0 ; i < t.nbele ; i++ ){
        printf("\n t(%d) = %d ",i+1,t.tab[i]);
   }
}
tableau doubl(tableau t){
   tableau t1 ;
   t1 = ctableau(t.nbele);
    for( int i = 0 ; i < t1.nbele ; i++ ){
       t1.tab[i] = t.tab[i]*2 ;
    }
    return t1 ;
}

int main() {
    int n ;
    printf(" veuillez sairie les element d'un tableau : ");
    scanf("%d",&n);
    tableau t = ctableau(n); 
    slecture(t);
    afficharge(t);
    tableau t1 ;
    t1 = doubl(t);
    printf(" voila le deuxieme tableau :\n");
    afficharge(t1);
    return 0;
}
