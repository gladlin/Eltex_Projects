#include "manyProcess.h"

int createManyProcess()
{
    pid_t pid1 = fork();
    if (pid1 == -1) {
        fprintf(stderr, "Ошибка при создании процесса 1\n");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0)
    {
        process1();
    }
    else
    {
        pid_t pid2 = fork();
        if (pid2 == -1) {
            fprintf(stderr, "Ошибка при создании процесса 2\n");
            exit(EXIT_FAILURE);
        }
        if (pid2 == 0)
        {
            process2();
        }
        else
        {
            if(waitForProcess(pid1, 1) == 0 || waitForProcess(pid2, 2) == 0)
                return 0;
            return 1;
        }
    }
    return 1;
}