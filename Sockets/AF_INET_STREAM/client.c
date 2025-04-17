#include "af_inet_stream.h"

int main()
{
    struct sockaddr_in client;
    int client_fd;
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == -1)
    {
        perror("socket");
        exit(1);
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(3425);
    client.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  


    if(connect(client_fd,(struct sockaddr *)&client, sizeof(client)) == -1)
    {
        perror("connect");
        close(client_fd);
        exit(1);
    }

    char message[SIZE_OF_BUF] = "Hello from client";
    if(send(client_fd, message, SIZE_OF_BUF, 0) == -1)
    {
        perror("send");
        close(client_fd);
        exit(1);
    }
    printf("\nКлиент отправил серверу сообщение: %s\n", message);

    char new_message[SIZE_OF_BUF];
    if(recv(client_fd, new_message, SIZE_OF_BUF, 0) == -1)
    {
        perror("recv");
        close(client_fd);
        exit(1);
    }
    printf("Клиент получил от сервера: %s\n", new_message);
    close(client_fd);

    return 0;
}