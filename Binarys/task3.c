#include "binaries.h"

void task3() {
  printf("\nTask 3\nPlease enter positive integer to convert to binary format: ");
  int number = 0;
  scanf("%d", &number);
  if (number <= 0) {
    printf("Please, enter positive integer\n");
    return;
  }

  int counter = 0;
  while (number != 0) {
    if ((number & 1) == 1) counter++;
    number >>= 1;
  }

  printf("Number of units equals %d\n", counter);
}
