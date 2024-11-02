#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *fich ;
    fich = fopen("informaton.txt","r");
    if ( fich == NULL){
        printf("Error");
        exit(0);
    }
    char a[10] ;
    printf( "%d",fgets(a,10,fich) );
    // char c;
    // while( (c = fgetc(fich)) != EOF ){
    //    printf("%c",c);
    // }
    // fseek( fich , -8 , SEEK_END );
    // printf("\n");
    // while( (c = fgetc(fich)) != EOF ){
    //    printf("%c",c);
    // }
    return 0;
}
