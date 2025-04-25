#include "server.h"

volatile sig_atomic_t stop = 0;

int main()
{
    struct sigaction sa;
    sa.sa_handler = handler_sigint;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(-1);
    }
    start_server();
    return 0;
}

void handler_sigint(){
    stop = 1;
}