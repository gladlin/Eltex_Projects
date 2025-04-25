#include "multicast.h"

int main()
{
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd == -1)
    {
        perror("socket client");
        return -1;
    }

    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    client_addr.sin_port = htons(PORT);

    if(bind(client_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)) == -1)
    {
        perror("bind");
        close(client_fd);
        return -1;
    }

    struct ip_mreq mreqn;
    mreqn.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
    mreqn.imr_interface.s_addr = htonl(INADDR_ANY);

    if(setsockopt(client_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreqn, sizeof(mreqn)) == -1)
    {
        perror("setsockopt");
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
    printf("Клиент получил сообщение от сервера: %s\n", buf);
    return 0;
}