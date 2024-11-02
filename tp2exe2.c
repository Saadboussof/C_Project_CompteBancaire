#include <stdio.h>
#include <stdlib.h>
int bino(int p, int n) {
    if (p == 0 || p == n) 
        return 1;
    else 
        return bino(p - 1, n - 1) + bino(p, n - 1);
}
int** binomialCoeffIterative(int n, int p) {
    int **C = (int**) malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        C[i] = (int*) malloc((p + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= (i < p ? i : p); j++) {
            if (j == 0 || j == i) // C(i, 0) = C(i, i) = 1
                C[i][j] = 1;
            else
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }

    return C; 
}
void affichage(int** C, int n, int p) {
    printf("Binomial Coefficient Matrix C(%d, %d):\n", n, p);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= (i < p ? i : p); j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int n, p;
    printf("Enter n and p (C(p, n)): ");
    scanf("%d %d", &n, &p);
    if (p > n || n < 0 || p < 0) {
        printf("Invalid input. Please ensure 0 <= p <= n.\n");
        return 1;
    }
    int c = bino(p, n);
    printf("Recursive method result: C(%d, %d) = %d\n", n, p, c);
    int **c1 = binomialCoeffIterative(n, p);
    affichage(c1, n, p);

    return 0;
}


// int ** combinaison(int n , int p){
//     int **c = (int **)malloc(sizeof(int*)*n*p) ;

// return c ;
// }