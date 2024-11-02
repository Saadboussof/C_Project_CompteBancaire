#include <stdio.h>
#include <math.h>

int fact(int n) {
    if (n == 0) return 1; 
    else return n * fact(n - 1); 
}

float cos1(int n, float x) {
    if (n == 0) {
        return 1 ; //cos(0) = 1
    } else {
        return (pow(-1, n) * pow(x, 2 * n) / fact(n)) + cos1(n - 1, x);
    }
}

int main() {
    int n; 
    float x; 

    printf("Enter the number of terms for the approximation (n): ");
    scanf("%d", &n);
    printf("Enter the angle in radians (x): ");
    scanf("%f", &x);
    int f = fact(n);
    printf("The factorial of %d is: %d\n", n, f);
    float d = cos1(n, x);
    printf("The approximate value of cos(%.2f) using %d terms is: %.5f\n", x, n, d);

    return 0;
}
