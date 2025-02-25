#include "manyProcess.h"

void process1()
{
    printf("\nПроцесс номер 1: Pid = %d, Ppid = %d\n", getpid(), getppid());
    pid_t pid3 = fork();
    if (pid3 == -1) {
        fprintf(stderr, "Ошибка при создании процесса 2\n");
        exit(EXIT_FAILURE);
    }
    if (pid3 == 0)
    {
        printf("Процесс номер 3: Pid = %d, Ppid = %d\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }

    pid_t pid4 = fork();
    if (pid4 == -1) {
        fprintf(stderr, "Ошибка при создании процесса 2\n");
        exit(EXIT_FAILURE);
    }
    if (pid4 == 0)
    {
        printf("Процесс номер 4: Pid = %d, Ppid = %d\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }
    if (waitForProcess(pid3, 3) == 0 || waitForProcess(pid4, 4) == 0)
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}