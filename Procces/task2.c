#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int createManyProcess();
void waitForProcess(pid_t pid, int number);
int createProcess5();
int create3and4Process();
pid_t createProcess(int number);

int createManyProcess() {
    pid_t pid1 = createProcess(1);
    pid_t pid2 = createProcess(2);
    if (pid1 == 0) {
        create3and4Process();
        exit(EXIT_SUCCESS);
    }

    if (pid2 == 0) {
        createProcess5();
        exit(EXIT_SUCCESS);
    }

    waitForProcess(pid1, 1);
    waitForProcess(pid2, 2);

    return 0;
}

int createProcess5() {
    pid_t pid5 = createProcess(5);
    waitForProcess(pid5, 5);
    return 0;
}

int create3and4Process() {
    pid_t pid3 = createProcess(3);
    pid_t pid4 = createProcess(4);

    waitForProcess(pid3, 3);
    waitForProcess(pid4, 4);

    return 0;
}

pid_t createProcess(int number) {
    //проблема в том, что дочерний процесс создается здесь и завершается здесь же, так как продолжает идти от момента выхова fork
    //можно сделать, что эта функция чисто будет проверять результат и вохвращать статус
    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Ошибка при создании процесса %d\n", number);
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
        printf("Процесс номер %d: Pid = %d, Ppid = %d\n", number, getpid(), getppid());
    return pid;
}

void waitForProcess(pid_t pid, int number) {
    int status;
    pid_t result = waitpid(pid, &status, 0);
    if (result == -1) {
        fprintf(stderr, "Ошибка при ожидании процесса %d\n", number);
        exit(EXIT_FAILURE);
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS) {
        fprintf(stderr, "Процесс %d завершился с ошибкой\n", number);
        exit(EXIT_FAILURE);
    }
}

int main() {
    if (createManyProcess() != 0) {
        printf("\nОшибки при выполнении кода\n");
        return -1;
    }
    return 0;
}