// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main() {
//     FILE *P, *K, *Q;

//     P = fopen("informaton.txt", "r");
//     if (P == NULL) {
//         printf("Error: Could not open 'informaton.txt' for reading.\n");
//         exit(1);
//     }
//     K = fopen("exemple.txt", "w+");
//     if (K == NULL) {
//         printf("Error: Could not open 'exemple.txt'.\n");
//         exit(1);
//     }
//     int i = 0;
//     while (fgetc(P) != EOF) {
//         i++;
//     }
//     printf("Number of characters in 'exemple.txt': %d\n", i);
//     char a[100];
//     // printf("Please enter a text in French: ");
//     // fgets(a, sizeof(a), stdin );
//     // fputs(a, K);

//     Q = fopen("saadd", "a+");
//     if (Q == NULL) {
//         printf("Error: Could not open 'saadd'.\n");
//         exit(1);
//     }
//     char b[10], n[10], m[10];
//     while (fscanf(P, "%s %s %s", b, n, m) != EOF) {
//         if (strcmp(b, "hasni") == 0 && strcmp(n, "hassan") == 0 && strcmp(m, "35") == 0) {
//             continue;  
//         }
//         fprintf(Q,"%s %s %s\n", b, n, m);
//     }
    
//     fclose(Q);
//     fclose(P);
//     fclose(K);
//     remove("informaton.txt");
//     rename("saadd","informaton.txt");
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *P, *K, *Q;
    P = fopen("informaton.txt", "r");
    if (P == NULL) {
        printf("Error: Could not open 'informaton.txt' for reading.\n");
        exit(1);
    }

    K = fopen("exemple.txt", "w+");
    if (K == NULL) {
        printf("Error: Could not open 'exemple.txt'.\n");
        exit(1);
    }
    int i = 0;
    while (fgetc(P) != EOF) {
        i++;
    }
    printf("Number of characters in 'informaton.txt': %d\n", i);
    rewind(P);
    // char a[100];
    // printf("Please enter a text in French: ");
    // fgets(a, sizeof(a), stdin );
    // fputs(a, K);
    Q = fopen("saad", "a+");
    if (Q == NULL) {
        printf("Error: Could not open 'saad'.\n");
        exit(1);
    }
    char b[10], n[10], m[10];
    while (fscanf(P, "%s %s %s", b, n, m) != EOF) {
        if (strcmp(b, "hasni") == 0 && strcmp(n, "hassan") == 0 && strcmp(m, "35") == 0) {
            continue;  
        }

        fprintf(Q, "%s %s %s\n", b, n, m);
    }
    fclose(Q);
    fclose(P);
    fclose(K);
    remove("informaton.txt");
    rename("saad", "informaton.txt");

    return 0;
}
