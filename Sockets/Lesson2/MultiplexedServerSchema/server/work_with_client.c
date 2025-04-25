#include "server.h"

int work_with_client_tcp(int fd)
{
    struct sockaddr_in client;
    socklen_t sizeof_client = sizeof(client);
    int client_fd;
    char buf[BUF_SIZE];

    client_fd = accept(fd, (struct sockaddr *)&client, &sizeof_client);
    if(client_fd  == -1)
    {
        perror("accept");
        return -1;
    }
    if(recv(client_fd, buf, BUF_SIZE, 0) == -1)
    {
        perror("recv tcp");
        close(client_fd);
        return -1;
    }

    if (strcmp(buf, "Запрос на время") == 0) 
    {
        time_t now = time(NULL);
        struct tm *local = localtime(&now);
        snprintf(buf, BUF_SIZE, "Time: %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);

    } else 
        snprintf(buf, BUF_SIZE, "Неверная команда");
    
    if(send(client_fd, buf, BUF_SIZE, 0) == -1)
    {
        perror("send tcp");
        close(client_fd);
        return -1;
    }

    close(client_fd);
    return 0;
}

int work_with_client_udp(int fd)
{
    struct sockaddr_in client;
    socklen_t sizeof_client = sizeof(client);
    char buf[BUF_SIZE];

    if(recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *)&client, &sizeof_client) == -1)
    {
        perror("recvfrom udp");
        return -1;
    }

    if (strcmp(buf, "Запрос на время") == 0) 
    {
        time_t now = time(NULL);
        struct tm *local = localtime(&now);
        snprintf(buf, BUF_SIZE, "Time: %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
    } else 
        snprintf(buf, BUF_SIZE, "Неверная команда");


    if(sendto(fd, buf, BUF_SIZE, 0, (struct sockaddr *)&client, sizeof_client) == -1)
    {
        perror("send udp");
        return -1;
    }
    return 0;
}