#include "broadcast.h"

int main()
{
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_fd == -1)
    {
        perror("socket server");
        return -1;
    }

    int broadcast_allow = 1;
    if(setsockopt(server_fd, SOL_SOCKET, SO_BROADCAST, &broadcast_allow, sizeof(broadcast_allow)) == -1)
    {
        perror("setsockopt");
        close(server_fd);
        return -1;
    }

    struct sockaddr_in broadcast;
    broadcast.sin_family = AF_INET;
    broadcast.sin_port = htons(PORT);
    broadcast.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    char buf[BUF_SIZE] = "Hello from server";
    socklen_t sizeofServer = sizeof(broadcast);
    if(sendto(server_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&broadcast, sizeofServer) == -1)
    {
        perror("sendto");
        close(server_fd);
        return -1;
    }
    printf("Сервер отправил сообщение устройствам\n");
    return 0;
}