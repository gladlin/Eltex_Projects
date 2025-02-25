#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int createSecondProcess();

int main()
{
    int res = createSecondProcess();
    if(res != 0)
    {
        printf("\nОшибки при выполнении кода");
        return -1;
    }
    return 0;
}

int createSecondProcess()
{
    pid_t pid;
    pid = fork ();
    if (pid <= -1)
    {
        perror ("Ошибка при создании копии процесса");
        exit(-1);
    }
    if (pid == 0) {
        printf("\nДочерний процесс: Pid = %d, ppid = %d\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("\nРодительский процесс: Pid = %d, ppid = %d\n", getpid(), getppid());
        int status;
        pid_t endProcess = wait(&status);
        if (status == -1)
        {
            perror("Ошибка при ожидании дочернего процесса");
            exit(-1);
        }
        if(WEXITSTATUS(status) != EXIT_SUCCESS || endProcess != pid)
        {
            perror("Ошибка при закрытии дочернего процесса");
            exit(-1);
        }
        else
            printf("Статус завершения дочернего процесса равен %d\n", WEXITSTATUS(status));
    }
    exit(0);
}