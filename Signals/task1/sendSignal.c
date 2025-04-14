#include "../signals.h"


int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Должен быть передан аргумент - pid процесса, которому надо послать сигнал, а также сам сигнал");
        exit(1);
    }

    pid_t pid = atoi(argv[1]);
    int sig = 0;
    if(strcmp(argv[2], "SIGUSR1") == 0)
        sig = SIGUSR1;
    else if(strcmp(argv[2], "SIGINT") == 0)
        sig = SIGINT;

    if(sig != 0 && kill(pid, sig) == -1)
    {
        perror("kill");
        exit(1);
    }
    
    printf("Сигнал был успешно отправлен\n");

    return 0;
}