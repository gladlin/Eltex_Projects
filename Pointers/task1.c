#include <stdio.h>

void enterThird(char *number, int third_byte) {
  number += 2;
  *number = third_byte;
}

void printBytes(char *number) {
  for (int i = 0; i < 4; i++) {
    printf("%d\t", *number);
    number++;
  }
}

int main() {
  int num = -1;
  char c;
  printf("Enter positive integer: ");
  if (scanf("%d%c", &num, &c) != 2 || c == '.' || num < 0)
    return -1;

  printf("Enter number, that must be entered in third byte: ");
  int third_byte = -1;
  if (scanf("%d%c", &third_byte, &c) != 2 || c == '.' || third_byte < 0)
    return -1;

  printBytes((char *)&num);
  enterThird((char *)&num, third_byte);
  printf("\nResult: %d\n", num);
  printBytes((char *)&num);
  return 0;
}