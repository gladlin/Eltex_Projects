#include <stdio.h>

int main() {
  int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int *point = array;
  for (int i = 0; i < (int)(sizeof(array) / sizeof(int)); i++) {
    printf("%d element of array is %d\n", i + 1, *point);
    point++;
  }
}