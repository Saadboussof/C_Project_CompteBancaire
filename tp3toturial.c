#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *P ;
    P = fopen("informaton.txt","r");
    if ( P == NULL ){
        printf(" Nn dzl ");
        exit(1);
    }
    // char createur[20];
    // int annee ;
    // printf(" entrer le nom : ");
    // scanf("%[^\n]s",createur);
    // printf(" l'annee de son naissance : ");
    // scanf("%d",&annee);

    // fprintf(P,"\n il est ENVOLVINGS par %s en %d",createur,annee); // fprintf using for writing in a file

    char a[10] , c ;
    
    while(  (c = fgetc(P)) != EOF ){
        printf("%c",c);
    }
    fclose(P);
    return 0;
}
// fwrite( address-var , taille-donne , nbr-donne , P ); 
// int pos = ftell(P) ; il donne la position de la dernier character ;  
//fgets( a , 10 , P )