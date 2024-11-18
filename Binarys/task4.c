#include <stdio.h>

void task4() {
    printf("\nTask 4\nEnter positive number, where is need to change third byte: ");
    int number = 0;
    scanf("%d", &number);
    if (number <= 0) {
        printf("Please, enter positive integer\n");
        return;
    }

    printf("\nPlease enter byte (0-255), which should be inserted into third byte: ");
    int byte = 0;
    scanf("%d", &byte);
    if (byte > 255 || byte < 0) {
        printf("Please, enter a valid byte (0-255)\n");
        return;
    }
    number &= (0xFF << 16);
    number |= (byte << 16);

    printf("Result: %u\n", number);
}
