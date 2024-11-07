#include "commonFunctions.h"

unsigned int **setRectangle(unsigned int n) {
  unsigned int **resultMatrix = malloc(sizeof(unsigned int *) * n);
  for (unsigned int i = 0; i < n; i++) {
    resultMatrix[i] = malloc(sizeof(unsigned int) * n);
  }
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      if (n - 1 - i == j || j >= -i + n)
        resultMatrix[i][j] = 1;
      else
        resultMatrix[i][j] = 0;
    }
  }
  return resultMatrix;
}