#include "server.h"

extern struct server servers[SERVERS_IN_POOL];

void listen_server(int listen_fd)
{
    char buf[BUF_SIZE];
    struct sockaddr_in client;
    socklen_t client_size = sizeof(client);
    while(!stop)
    {
        if(recvfrom(listen_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&client, &client_size) == -1)
        {
            perror("recvfrom");
        }
        for(int i = 0; i < SERVERS_IN_POOL; i++)
        {
            if(servers[i].is_busy == 0)
            {
                snprintf(buf, BUF_SIZE, "%d", servers[i].port);
                if(sendto(listen_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&client, client_size) == -1)
                {
                    perror("sendto");
                }
                break;
            }
        }
    }
    printf("Сервер завершил работу корректно.\n");
}

void *child_server(void *arg)
{
    struct server *this_server = (struct server *)arg;
    struct sockaddr_in server_addr;
    if(create_socket(&this_server->server_fd, &server_addr, this_server->port) == -1)
        return NULL;

    char buf[BUF_SIZE];
    struct sockaddr_in client;
    socklen_t client_size = sizeof(client);
    while(!stop)
    {
        if(recvfrom(this_server->server_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&client, &client_size) == -1)
        {
            perror("recvfrom");
            return NULL;
        }
        this_server->is_busy = 1;
        if(strcmp(buf, "Запрос на время\n") != 0)
            strncpy(buf, "Неверная команда", BUF_SIZE);
        else
        {
            time_t mytime = time(NULL);
            struct tm *now = localtime(&mytime);
            if(snprintf(buf, BUF_SIZE, "Time: %d:%d:%d\n", now->tm_hour, now->tm_min, now->tm_sec) == 0)
            {
                perror("snprintf server");
                close(this_server->server_fd);
                return NULL;
            }
        }
        if(sendto(this_server->server_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&client, client_size) == -1)
        {
            perror("snprintf server");
            close(this_server->server_fd);
            return NULL;
        }
        this_server->is_busy = 0;
        printf("\nСервер отправил время клиенту\n");
    }
    return NULL;
}