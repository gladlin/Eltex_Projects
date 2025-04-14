#include "../signals.h"

void handle_sigusr1(int sig) {
    printf("Получен сигнал SIGUSR1 (сигнал %d)\n", sig);
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(sigaction(SIGUSR1, &sa, NULL) != 0)
    {
        perror("sigaction");
        exit(1);
    }

    printf("Была проведена диспозиция сигнала SIGUSR1\n");
    printf("PID этого процесса: %d\n", getpid());
    while(1)
    {
        if (pause() == -1)
            break;
    }

    return 0;
}