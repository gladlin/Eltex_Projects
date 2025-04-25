#include "server.h"

extern pthread_t *threads;
extern struct server *servers;
extern int count_server;

int create_pool() 
{
    int listen_server_fd;
    struct sockaddr_in listen_server_addr;
    if (create_socket(&listen_server_fd, &listen_server_addr, PORT) == -1)
        return -1;

    threads = calloc(count_server, sizeof(pthread_t));
    servers = calloc(count_server, sizeof(struct server));
    if (threads == NULL || servers == NULL) 
    {
        perror("calloc server");
        exit(-1);
    }

    for (int i = 0; i < count_server; i++) 
    {
        servers[i].is_busy = 0;
        servers[i].port = PORT + 1 + i;
        servers[i].waiting_time = 0;
        servers[i].is_dynamic = 0;
        if (pthread_create(&threads[i], NULL, child_server, &servers[i]) != 0) 
        {
            perror("pthread_create server");
            exit(-1);
        }
    }

    return listen_server_fd;
}

int manage_server_pool() 
{
    int all_busy = 1;
    for (int i = 0; i < count_server; i++) 
    {
        if (servers[i].is_dynamic && servers[i].waiting_time > 10) 
        {
            printf("Закрыл дескриптор %d", servers[i].port); // закрывает оба сервера после первого сообщения
            pthread_cancel(threads[i]);
            pthread_join(threads[i], NULL);
            for (int j = i; j < count_server - 1; j++) 
            {
                servers[j] = servers[j + 1];
                threads[j] = threads[j + 1];
            }
            count_server--;
            servers = realloc(servers, count_server * sizeof(struct server));
            threads = realloc(threads, count_server * sizeof(pthread_t));
            void *tmp1 = realloc(servers, count_server * sizeof(struct server));
            if (!tmp1) {
                perror("realloc servers");
                exit(-1);
            }
            servers = tmp1;
            void *tmp2 = realloc(threads, count_server * sizeof(pthread_t));
            if (!tmp2) {
                perror("realloc threads");
                exit(-1);
            }
            threads = tmp2;
            i--;
        }
        if (servers[i].is_busy == 0)
            all_busy = 0;
    }

    if (all_busy) 
    {
        count_server++;
        servers = realloc(servers, count_server * sizeof(struct server));
        threads = realloc(threads, count_server * sizeof(pthread_t));
        if (!servers || !threads) 
        {
            perror("realloc");
            exit(-1);
        }
        servers[count_server - 1].is_busy = 0;
        servers[count_server - 1].port = PORT + count_server;
        servers[count_server - 1].waiting_time = 0;
        servers[count_server - 1].is_dynamic = 1;
        pthread_create(&threads[count_server - 1], NULL, child_server, &servers[count_server - 1]);
    }
    return 0;
}