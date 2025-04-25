#include "server_client.h"

int main()
{
    struct sockaddr_in client;
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == -1)
    {
        perror("socket client");
        exit(1);
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(3425);
    client.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    
    if(connect(client_fd, (struct sockaddr *)&client, (sizeof(client))) == -1)
    {
        perror("connect client");
        close(client_fd);
        exit(1);
    }

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

    if(send(client_fd, buf, BUF_SIZE, 0) == -1)
    {
        perror("send client");
        close(client_fd);
        exit(1);
    }

    printf("Клиент отправил сообщение серверу: %s\n", buf);
    
    if(recv(client_fd, buf, BUF_SIZE, 0) == -1)
    {
        perror("recv client");
        close(client_fd);
        exit(1);
    }

    printf("Клиент получил от сервера сообщение: %s\n", buf);

    close(client_fd);
    return 0;
}