#include "binaries.h"

void task2() {
  int number = 0;
  printf("\nTask 2\nPlease enter negative integer to convert to binary format: ");
  scanf("%d", &number);
  if (number >= 0) {
    printf("Please, enter negative integer\n");
    return;
  }

  int len_bin_number = 1;
  int temp = number;

  while ((temp >> 1) != -1) {
    len_bin_number++;
    temp >>= 1;
  }

  while (len_bin_number >= 0) {
    int bit = (number >> len_bin_number) & 1;
    printf("%d", bit);
    len_bin_number--;
  }
  printf("\n");
}
