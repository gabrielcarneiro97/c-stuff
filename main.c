#include <stdio.h>
#include <stdlib.h>


int main() {
  int *p;
  int a = 10;

  p = &a;

  printf("%d\n", *p);
  return 0;
}
