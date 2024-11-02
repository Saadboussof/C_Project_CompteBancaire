#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    FILE *P ;
    P = fopen("saad","r");
    if ( P == NULL ){
        printf("nn");
        exit(1);
    }
    int pos , i , c ;
    fseek(P, 0, SEEK_END);
    pos = ftell(P);
    for (i = 1 ; i <= pos ; i++ ){
       fseek( P , -i , SEEK_END);
       c = fgetc( P );
       printf("%c",c);
    }
    return 0 ;
}