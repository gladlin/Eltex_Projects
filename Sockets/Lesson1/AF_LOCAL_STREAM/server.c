#include "af_local_stream.h"

int main()
{
    struct sockaddr_un server, client;
    socklen_t peer_addr_size;
    int server_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    int client_fd;
    if(server_fd == -1)
    {
        perror("socket");
        exit(1);
    }
    memset(&server, 0, sizeof(server));

    
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, MY_SOCK_PATH, sizeof(server.sun_path));


    if(bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("bind");
        close(server_fd);
        unlink(MY_SOCK_PATH);
        exit(1);
    }

    if(listen(server_fd, BACKLOG) == -1)
    {
        perror("listen");
        close(server_fd);
        unlink(MY_SOCK_PATH);
        exit(1);
    }

    peer_addr_size = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr *)&client, &peer_addr_size);
    if(client_fd == -1)
    {
        perror("accept");
        close(server_fd);
        unlink(MY_SOCK_PATH);
        exit(1);
    }

    char buf[SIZE_OF_BUF];
    if(recv(client_fd, buf, SIZE_OF_BUF, 0) == -1)
    {
        perror("recv");
        close(client_fd);
        close(server_fd);
        unlink(MY_SOCK_PATH);
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
        unlink(MY_SOCK_PATH);
        exit(1);
    }

    printf("Сервер отправил строку клиенту\n");

    close(client_fd);
    close(server_fd);
    unlink(MY_SOCK_PATH);


    return 0;
}