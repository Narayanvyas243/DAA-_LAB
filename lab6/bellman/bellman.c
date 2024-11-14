#include <stdio.h>
int helo(int n);
int main() {
  printf("sum = %d", helo(3));
  return 0;
}

int helo(int n) {
  if (n == 1) {
    return 1;
  }
  return n * helo(n - 1);
}
 