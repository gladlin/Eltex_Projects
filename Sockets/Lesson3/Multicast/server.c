#include "multicast.h"

int main()
{
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_fd == -1)
    {
        perror("socket server");
        return -1;
    }

    struct sockaddr_in server;
    
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(MULTICAST_IP);

    char buf[BUF_SIZE] = "Hello from server";

    socklen_t sizeofServer = sizeof(server);
    if(sendto(server_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&server, sizeofServer) == -1)
    {
        perror("sendto");
        close(server_fd);
        return -1;
    }
    printf("Сервер отправил сообщение клиентам\n");
    return 0;
}