#include "handbook.h"

char *write_to_string() {
  char buffer[LEN_OF_ARG + 2];
  char *result;

  if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
    printf("Ошибка ввода!\n");
    return NULL;
  }

  size_t len = strlen(buffer);
  if (buffer[len - 1] != '\n' || (len == 1)) {
    printf("Превышена длина строки (максимум %d символов)!\n", LEN_OF_ARG);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    return NULL;
  }

  buffer[len - 1] = '\0';

  result = malloc(len);
  if (result == NULL) {
    printf("Ошибка выделения памяти!\n");
    return NULL;
  }

  strcpy(result, buffer);
  return result;
}

int get_first_empty() {
  for (int i = 0; i < N; i++) {
    if (list_of_abonents[i].name[0] == '\0' &&
        list_of_abonents[i].second_name[0] == '\0' &&
        list_of_abonents[i].tel[0] == '\0')
      return i;
  }
  return -1;
}