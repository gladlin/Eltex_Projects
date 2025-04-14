#include "../signals.h"

int main()
{
    sigset_t set;
    if(sigemptyset(&set) != 0)
    {
        perror("sigemptyset");
        exit(1);
    }

    if(sigaddset(&set, SIGUSR1) != 0)
    {
        perror("sigaddset");
        exit(1);
    }

    if(sigprocmask(SIG_BLOCK, &set, NULL) == -1)
    {
        perror("sigprocmask");
        exit(1);
    }
    printf("PID процесса: %d\n", getpid());
    int sig;
    while(1)
    {
        if(sigwait(&set, &sig) != 0)
        {
            perror("sigwait");
            exit(1);
        }
        else
            printf("Полученный сигнал: %d\n", sig);     
    }
    return 0;
}