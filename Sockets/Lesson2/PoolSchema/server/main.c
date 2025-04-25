#include "server.h"

volatile sig_atomic_t stop = 0; 
struct server servers[SERVERS_IN_POOL]; 

int main()
{
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if(sigaction(SIGINT, &sa, NULL) != 0)
    {
        perror("sigaction");
        exit(1);
    }

    int listen_fd;
    struct sockaddr_in listen_server_addr;
    if(create_socket(&listen_fd, &listen_server_addr, PORT_LISTEN) == -1)
        printf("Ошибка при создании сервера\n");

    pthread_t threads[SERVERS_IN_POOL];
    for(int i = 0; i < SERVERS_IN_POOL; i++)
    {
        servers[i].is_busy = 0;
        servers[i].port = PORT_LISTEN + 1 + i;
        struct server *server_new = &servers[i];
        if(pthread_create(&threads[i], NULL, child_server, (void *)server_new) == -1)
        {
            perror("pthread_create");
            close(listen_fd);
            exit(1);
        }
    }
    listen_server(listen_fd);

    for(int i = 0; i < SERVERS_IN_POOL; i++)
    {
        if(pthread_join(threads[i], NULL) == -1)
            perror("pthread_join");
        close(servers[i].server_fd);
    }
    close(listen_fd);
    return 0;
}