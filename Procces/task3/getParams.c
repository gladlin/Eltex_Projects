#include "execute.h"

int getParams() {
  char path[128] = {0};
  char options[64] = {0};
  while (1) {
    printf("\nВведите путь к программе: ");
    if (fgets(path, sizeof(path), stdin) == NULL) {
      printf("Ошибка ввода!\n");
      continue;
    }

    size_t len = strlen(path);
    if (len > 0 && path[len - 1] == '\n') {
      path[len - 1] = '\0';
    }

    if (strcmp(path, "exit") == 0) {
      printf("Завершение работы\n");
      break;
    }

    printf("Введите опции для запуска программы: ");
    if (fgets(options, sizeof(options), stdin) == NULL) {
      printf("Ошибка ввода!\n");
      continue;
    }

    // удаление лишнего символа перевода строки
    len = strlen(options);
    if (len > 0 && options[len - 1] == '\n') {
      options[len - 1] = '\0';
    }

    int res = executeProgram(path, options);
    if (res == -1) {
      printf("Ошибка при выполнении программы.\n");
      exit(-1);
    }
  }
  exit(0);
}