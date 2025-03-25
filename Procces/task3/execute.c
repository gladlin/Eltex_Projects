#include "execute.h"

int executeProgram(const char *path, const char *options) {
  pid_t pid = fork();

  if (pid == 0) {
    char *args[64]; // массив аргументов для execvp
    int i = 0;

    // первый аргумент - сама программа
    args[i++] = (char *)path;

    char *token = strtok((char *)options, " ");
    while (token != NULL && i < 63) {
      args[i++] = token;
      token = strtok(NULL, " ");
    }

    args[i] = NULL;

    if (execvp(path, args) == -1) {
      perror("Ошибка выполнения программы");
      exit(EXIT_FAILURE);
    }

  } else if (pid > 0) {
    int status;
    pid_t newpid = waitpid(pid, &status, 0);
    if (newpid == -1) {
      perror("Ошибка при ожидании процесса");
      return -1;
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS) {
      fprintf(stderr, "Процесс завершился с ошибкой\n");
      return -1;
    }
  } else {
    perror("Ошибка создания процесса");
    return -1;
  }

  return 0;
}