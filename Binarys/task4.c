#include "binaries.h"

void task4() {
  printf("\nTask 4\nEnter positive number, where is need to change third byte: ");
  int number = 0;
  scanf("%d", &number);
  if (number <= 0) {
    printf("Please, enter positive integer\n");
    return;
  }

  printf("\nPlease enter digit, what should be insert into third byte: ");
  int byte = -1;
  scanf("%d", &byte);
  if (byte < 0) {
    printf("Please, enter positive byte\n");
    return;
  }

  if (byte == 1)
    number |= (byte << 2);
  else if (byte == 0)
    number &= ~(1 << 2);

  printf("Result: %d\n", number);
}
