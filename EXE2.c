#include <stdio.h>
#include <stdlib.h>
int* create( int n ){
  int *p ;
  p = (int*)malloc(n*sizeof(int));
  return p ;
}
int main() {
  int *p ;
  int n ;
 
  printf(" n = ");
  scanf("%d",&n);
  p = create(n);
  for (int i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("%d ", p[i]);
  }
    return 0;
}