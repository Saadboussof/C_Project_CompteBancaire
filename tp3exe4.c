#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main() {
    FILE *F,*P;
    int A[MAX] ; 
    F = fopen("exebi.bin", "wb");
    if (F == NULL) {
        printf(" Error.\n");
        return 1;
    }
    for (int i = 0 ; i<MAX ; i++){
      A[i] = i+1 ;
    }
    fwrite( A , sizeof(int) , MAX , F );
    // rewind(F);
    fclose(F);
    P = fopen("exebi.bin", "rb");
    if (P == NULL) {
        printf(" Error.\n");
        return 1;
    }
    int B[MAX];

    fread(B , sizeof(int) ,MAX , F);
    for (int i = 0 ; i<MAX ; i++){
      printf("%d\n",B[i]);
    }
    fclose(P);
    fclose(F);
     return 0;
}
