#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file;
    int nf; 
    float *F; 
    file = fopen("exemplemodif.txt", "r");
    if (file == NULL) {
        printf(" Error.\n");
        return 1;
    }
    fscanf(file, "%d", &nf);
    F = (float *)malloc(nf * sizeof(float));
    int i ;
    for (i = 0 ; i < nf ; i++) {
        fscanf(file, "%f", &F[i]);
    }
    fclose(file);
    printf("Number of float values: %d\n", nf);
    printf("Float values:\n");

    for (int i = 0; i < nf; i++) {
        printf("%.3f ", F[i]);
    }
    printf("\n");
    free(F);
    rename("exemplemodif.txt","exemple.txt");
    return 0;
}
