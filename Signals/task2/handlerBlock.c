#include "../signals.h"

int main()
{
    sigset_t set;
    if(sigemptyset(&set) != 0)
    {
        perror("sigemptyset");
        exit(1);
    }

    if(sigaddset(&set, SIGINT) != 0)
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
    while(1)
    {
        pause();        
    }
    return 0;
}