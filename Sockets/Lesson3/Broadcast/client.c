#include "broadcast.h"

int main()
{
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd == -1)
    {
        perror("socket server");
        return -1;
    }

    struct sockaddr_in broadcast;
    broadcast.sin_family = AF_INET;
    broadcast.sin_port = htons(PORT);
    broadcast.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t sizeofServer = sizeof(broadcast);

    if(bind(client_fd, (struct sockaddr *)&broadcast, sizeofServer) == -1)
    {
        perror("socket server");
        close(client_fd);
        return -1;
    }
    char buf[BUF_SIZE];
    if(recvfrom(client_fd, buf, BUF_SIZE, 0, NULL, NULL) == -1)
    {
        perror("recvfrom");
        close(client_fd);
        return -1;
    }
    printf("Клиент получил от сервера: %s\n", buf);
    return 0;
}