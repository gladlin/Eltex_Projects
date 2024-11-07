#include "commonFunctions.h"

unsigned int **snailMatrix(short int n) {
  int value = 1;
  short int left = 0;
  short int right = n - 1;
  short int top = 0;
  short int down = n - 1;

  unsigned int **resultMatrix = malloc(sizeof(int *) * (long unsigned)n);
  for (int i = 0; i < n; i++) {
    resultMatrix[i] = malloc(sizeof(int) * (long unsigned)n);
  }

  while (value <= n * n) {
    for (int i = left; i <= right; i++) {
      resultMatrix[top][i] = value;
      value++;
    }
    top++;

    for (int i = top; i <= down; i++) {
      resultMatrix[i][right] = value;
      value++;
    }
    right--;
    for (int i = right; i >= left; i--) {
      resultMatrix[down][i] = value;
      value++;
    }

    down--;
    for (int i = down; i >= top; i--) {
      resultMatrix[i][left] = value;
      value++;
    }
    left++;
  }
  return resultMatrix;
}
