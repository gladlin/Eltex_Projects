#include "commonFunctions.h"

unsigned int **fillMatrix(unsigned int n) {
  unsigned int **resultMatrix = malloc(sizeof(unsigned int *) * n);
  for (unsigned int i = 0; i < n; i++) {
    resultMatrix[i] = malloc(sizeof(unsigned int) * n);
  }

  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      resultMatrix[i][j] = i * n + j + 1;
    }
  }
  return resultMatrix;
}
