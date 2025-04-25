#include "server_client.h"

int main()
{
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if(client_fd == -1)
    {
        perror("socket client");
        exit(1);
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_LISTEN);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    socklen_t server_len = sizeof(server);
    char message[BUF_SIZE];
    if(fgets(message, BUF_SIZE, stdin) == NULL)
    {
        perror("fgets client");
        close(client_fd);
        exit(3);
    }

    if(sendto(client_fd, message, BUF_SIZE, 0, (struct sockaddr*)&server, server_len) == -1)
    {
        perror("send client");
        close(client_fd);
        exit(4);
    }

    char port[BUF_SIZE];
    if(recvfrom(client_fd, port, BUF_SIZE, 0, (struct sockaddr*)&server, &server_len) == -1)
    {
        perror("recv client");
        close(client_fd);
        exit(4);
    }
    printf("Клиент получил от сервера: %s\n", port);

    int port_int = atoi(port);
    if(port_int == 0)
    {
        perror("atoi client");
        close(client_fd);
        exit(5);
    }

    server.sin_port = htons(port_int);
    if(sendto(client_fd, message, BUF_SIZE, 0, (struct sockaddr *)&server, server_len) == -1)
    {
        perror("send client");
        close(client_fd);
        exit(4);
    }

    if(recvfrom(client_fd, message, BUF_SIZE, 0, (struct sockaddr *)&server, &server_len) == -1)
    {
        perror("recv client");
        close(client_fd);
        exit(4);
    }
    printf("Клиент получил от сервера: %s\n", message);
    close(client_fd);
    return 0;
}