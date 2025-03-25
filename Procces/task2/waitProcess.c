#include "manyProcess.h"

int waitForProcess(pid_t pid, int number) {
    int status;
    pid_t result = waitpid(pid, &status, 0);
    if (result == -1) {
        perror("Ошибка при ожидании процесса \n");
        return -1;
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS) {
        fprintf(stderr, "Процесс %d завершился с ошибкой\n", number);
        return -1;
    }
    return 1;
}