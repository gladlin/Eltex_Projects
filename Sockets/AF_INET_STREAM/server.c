#include "af_inet_stream.h"

#define BACKLOG 1

int main()
{
    int client_fd, server_fd;
    struct sockaddr_in server, client;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1)
    {
        perror("socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(3425);
    server.sin_addr.s_addr = htonl(INADDR_ANY);    
    if(bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("bind");
        close(server_fd);
        exit(1);
    }

    if(listen(server_fd, BACKLOG) == -1)
    {
        perror("listen");
        close(server_fd);
        exit(1);
    }
    
    socklen_t sizeof_client = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr *)&client, &sizeof_client);
    if(client_fd == -1)
    {
        perror("accept");
        close(server_fd);
        exit(1);
    }

    char buf[SIZE_OF_BUF];
    if(recv(client_fd, buf, SIZE_OF_BUF, 0) == -1)
    {
        perror("recv");
        close(client_fd);
        close(server_fd);
        exit(1);
    }

    printf("Сервер принял строку: %s\n", buf);
    buf[0] = '8';
    printf("Сервер изменил строку на: %s\n", buf);

    if(send(client_fd, buf, SIZE_OF_BUF, 0) == -1)
    {
        perror("send");
        close(client_fd);
        close(server_fd);
        exit(1);
    }
    printf("Сервер отправил строку клиенту\n");

    close(client_fd);
    close(server_fd);

    return 0;
}