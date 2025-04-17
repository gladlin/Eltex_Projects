#include "af_local_dgram.h"

int main()
{
    struct sockaddr_un client, server;
    int client_fd;
    client_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(client_fd == -1)
    {
        perror("socket");
        exit(1);
    }

    memset(&client, 0, sizeof(client));
    client.sun_family = AF_LOCAL;
    strncpy(client.sun_path, MY_SOCK_PATH_CLIENT, sizeof(client.sun_path));
    if (bind(client_fd, (struct sockaddr *)&client, sizeof(client)) == -1)
    {
        perror("bind");
        close(client_fd);
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, MY_SOCK_PATH_SERVER, sizeof(server.sun_path));

    char message[SIZE_OF_BUF] = "Hello from client";
    if(sendto(client_fd, message, SIZE_OF_BUF, 0, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("sendto");
        close(client_fd);
        unlink(MY_SOCK_PATH_CLIENT);
        exit(1);
    }
    printf("\nКлиент отправил серверу сообщение: %s\n", message);

    char new_message[SIZE_OF_BUF];
    if(recvfrom(client_fd, new_message, SIZE_OF_BUF, 0, NULL, NULL) == -1)
    {
        perror("recvfrom");
        close(client_fd);
        unlink(MY_SOCK_PATH_CLIENT);
        exit(1);
    }
    printf("Клиент получил от сервера: %s\n", new_message);

    close(client_fd);
    unlink(MY_SOCK_PATH_CLIENT);
    return 0;
}