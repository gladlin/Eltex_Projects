#include "server.h"

int create_socket_udp(int *fd, struct sockaddr_in *sock)
{
    *fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(*fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    memset(sock, 0, sizeof(*sock));
    sock->sin_family = AF_INET;
    sock->sin_port = htons(UDP_PORT);
    sock->sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t sizeof_sock = sizeof(*sock);
    if(bind(*fd, (struct sockaddr *)sock, sizeof_sock) == -1)
    {
        perror("bind udp");
        close(*fd);
        exit(-1);
    }

    return 0;
}

int create_tcp_socket(int *fd, struct sockaddr_in *sock)
{
    *fd = socket(AF_INET, SOCK_STREAM, 0);
    if(*fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    memset(sock, 0, sizeof(*sock));
    sock->sin_family = AF_INET;
    sock->sin_port = htons(TCP_PORT);
    sock->sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t sizeof_sock = sizeof(*sock);
    if(bind(*fd, (struct sockaddr *)sock, sizeof_sock) == -1)
    {
        perror("bind tcp");
        close(*fd);
        exit(-1);
    }
    if(listen(*fd, BACKLOG) == -1)
    {
        perror("listen");
        close(*fd);
        exit(-1);
    }
    return 0;
}