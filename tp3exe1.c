#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *P , *K;
    P = fopen("informaton.txt","r");
    if ( P == NULL) {
        printf("NN NN");
        exit(1);
    }
    K = fopen("exemple.txt","a+");
    if ( K == NULL ){
        printf("NrN NN");
        exit(1);
    }
    
    char str[100];
    printf("veuillez saisir un text et en stocker dans : \n");
    fgets(str, sizeof(str), stdin);
    fputs(str,K);
    char c;
    c = fgetc(P) ;
    while( c != EOF ){
      fputc(c,K);
      c = fgetc(P);
    }
    int i ;
    char c[10] ;
    do{
      i++;
      c = fgetc(P);
    }while( c != EOF );
    printf(" les nombers des characters de fichie est %d ", i-1 );

    fclose(P);
    fclose(K);
    return 0;
}
 