#include "manyProcess.h"

void process2()
{
    printf("Процесс номер 2: Pid = %d, Ppid = %d\n", getpid(), getppid());
    pid_t pid5 = fork();
    if (pid5 == -1) {
        fprintf(stderr, "Ошибка при создании процесса 5\n");
        exit(EXIT_FAILURE);
    }
    if (pid5 == 0)
    {
        printf("Процесс номер 5: Pid = %d, Ppid = %d\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }
    if (waitForProcess(pid5, 5) == 0)
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}