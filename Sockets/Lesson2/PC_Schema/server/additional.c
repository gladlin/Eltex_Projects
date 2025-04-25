#include "server.h"

int create_socket(int *fd, struct sockaddr_in *addr, int port) 
{
    *fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*fd == -1) 
    {
        perror("socket server");
        return -1;
    }

    memset(addr, 0, sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(*fd, (struct sockaddr*)addr, sizeof(*addr)) == -1) 
    {
        perror("bind server");
        close(*fd);
        return -1;
    }

    return 0;
}

void handle_sigint() 
{
    stop = 1;
}
