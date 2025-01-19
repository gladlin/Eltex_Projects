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

void free_all() {
  struct abonent *current_Abonent = head;
  while (current_Abonent != NULL) {
    struct abonent *next = current_Abonent->next;
    free(current_Abonent);
    current_Abonent = next;
  }
  head = NULL;
  tail = NULL;
}