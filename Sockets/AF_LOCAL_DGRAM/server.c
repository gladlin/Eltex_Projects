#include "af_local_dgram.h"

int main()
{
    int server_fd;
    struct sockaddr_un server, client;

    server_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(server_fd == -1)
    {
        perror("socket");
        exit(1);
    }

    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, MY_SOCK_PATH_SERVER, sizeof(server.sun_path));

    if(bind(server_fd, (struct sockaddr *)&server, (socklen_t)sizeof(server)) == -1)
    {
        perror("bind");
        close(server_fd);
        unlink(MY_SOCK_PATH_SERVER);
        exit(1);
    }

    char buf[SIZE_OF_BUF];
    int sizeOfClient = sizeof(client);

    if(recvfrom(server_fd, buf, SIZE_OF_BUF, 0, (struct sockaddr *)&client, (socklen_t *)&sizeOfClient) == -1)
    {
        perror("recvfrom");
        close(server_fd);
        unlink(MY_SOCK_PATH_SERVER);
        exit(1);
    }

    printf("Сервер принял строку: %s\n", buf);
    buf[0] += 1;
    printf("Сервер изменил строку на: %s\n", buf);

    if(sendto(server_fd, buf, SIZE_OF_BUF, 0, (struct sockaddr *)&client, (socklen_t)sizeOfClient) == -1)
    {
        perror("sendto");
        close(server_fd);
        unlink(MY_SOCK_PATH_SERVER);
        exit(1);
    }
    printf("Сервер отправил строку клиенту\n");
    close(server_fd);
    unlink(MY_SOCK_PATH_SERVER);

    return 0;
}