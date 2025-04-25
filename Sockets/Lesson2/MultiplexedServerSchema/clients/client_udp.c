#include "clients.h"

int main()
{
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd == -1)
    {
        perror("socket client");
        exit(-1);
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(UDP_PORT);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    socklen_t sizeofServer = sizeof(server);

    char buf[BUF_SIZE];
    printf("Введите сообщение для сервера: ");
    if(fgets(buf, BUF_SIZE, stdin) == NULL)
    {
        perror("fgets client");
        close(client_fd);
        exit(1);
    }
    
    char *p = strpbrk(buf, "\n");
    *p = '\0';

    if(sendto(client_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&server, sizeofServer) == -1)
    {
        perror("sendto client");
        close(client_fd);
        exit(1);
    }

    printf("Клиент отправил сообщение серверу: %s\n", buf);
    
    if(recvfrom(client_fd, buf, BUF_SIZE, 0, NULL, NULL) == -1)
    {
        perror("recvfrom client");
        close(client_fd);
        exit(1);
    }

    printf("Клиент получил от сервера сообщение: %s\n", buf);

    close(client_fd);
    return 0;
}