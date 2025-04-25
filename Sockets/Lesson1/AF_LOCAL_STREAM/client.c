#include "af_local_stream.h"

int main()
{
    struct sockaddr_un client;
    int client_fd;
    client_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(client_fd == -1)
    {
        perror("socket");
        exit(1);
    }

    memset(&client, 0, sizeof(client));
    client.sun_family = AF_LOCAL;
    if(strncpy(client.sun_path, MY_SOCK_PATH, sizeof(client.sun_path)) == NULL)
    {
        perror("strncpy");
        close(client_fd);
        exit(1);
    }

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
    unlink(MY_SOCK_PATH);

    return 0;
}