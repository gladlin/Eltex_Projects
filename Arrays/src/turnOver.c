#include "commonFunctions.h"

int *writeArray(unsigned int n) {
  int *resultArray = malloc(sizeof(int) * n);
  for (unsigned int i = 0; i < n; i++) {
    int newValue = 0;
    char c = ' ';
    printf("Enter integer: ");
    if (scanf("%d%c", &newValue, &c) != 2 || c == '.') {
      printf("Was entered not an integer");
      free(resultArray);
      return NULL;
    } else
      resultArray[i] = newValue;
  }
  return resultArray;
}
