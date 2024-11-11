#include "commonFunctions.h"

void printMatrix(unsigned int **matrix, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = 0; j < n; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
    free(matrix[i]);
  }
  free(matrix);
}

void printArray(int *array, unsigned int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", array[i]);
  }
  free(array);
}