#include "commonFunctions.h"
#include <stdio.h>

int main() {
  int first = 0;
  char c = ' ';
  printf("Enter size of rectangle matrix: ");
  if (scanf("%d%c", &first, &c) != 2 || first < 1 || c == '.') {
    printf("Invalid input\n");
    return -1;
  }
  unsigned int n = first;

  printf("Task 1\n");
  unsigned int **filledMatrix = fillMatrix(n);
  printMatrix(filledMatrix, n);

  printf("Task 2\n");
  unsigned int **matrix = setRectangle(n);
  printMatrix(matrix, n);

  printf("Task 3\n");
  int *array = writeArray(n);
  if (array != NULL)
    printArray(array, n);
  else
    printf("Error in input.\n");

  printf("\nTask 4\n");
  unsigned int **snailMatrixResult = snailMatrix(n);
  printMatrix(snailMatrixResult, n);

  return 0;
}