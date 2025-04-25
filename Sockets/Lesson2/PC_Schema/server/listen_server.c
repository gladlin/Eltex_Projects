#include "server.h"

pthread_t *threads;
struct server *servers;
int count_server = START_COUNT_SERVERS;

int listen_server(mqd_t client_mq) 
{
    int listen_server_fd = create_pool();
    if (listen_server_fd == -1) 
    {
        clear_all(client_mq, threads, servers, count_server);
        exit(-1);
    }

    struct sockaddr_in client;
    socklen_t sizeclient = sizeof(client);
    char buf[BUF_SIZE];

    while (!stop) 
    {
        if (recvfrom(listen_server_fd, buf, BUF_SIZE, 0, (struct sockaddr*)&client, &sizeclient) == -1) 
        {
            perror("recvfrom server");
            break;
        }
        if(stop)
            break;

        if (mq_send(client_mq, (const char *)&client, sizeof(struct sockaddr_in), 0) == -1) 
        {
            perror("mq_send server");
            break;
        }

        if (manage_server_pool() == -1)
            break;
    }

    clear_all(client_mq, threads, servers, count_server);
    return 0;
}

void clear_all(mqd_t mq, pthread_t *threads, struct server *servers, int count) 
{
    if (mq != (mqd_t)-1) 
    {
        mq_close(mq);
        mq_unlink(MQ_NAME);
    }

    if (threads != NULL) 
    {
        for (int i = 0; i < count; i++) 
        {
            pthread_cancel(threads[i]);
            pthread_join(threads[i], NULL);
        }
        free(threads);
    }

    if (servers != NULL) 
        free(servers);
}
