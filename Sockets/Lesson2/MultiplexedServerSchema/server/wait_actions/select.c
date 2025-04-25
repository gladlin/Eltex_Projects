#include "../server.h"

void wait_action(int tcp_fd, int udp_fd)
{
    fd_set readfds;
    int max_fd = (tcp_fd > udp_fd) ? tcp_fd : udp_fd;
    struct timeval tv;
    while(!stop)
    {
        FD_ZERO(&readfds);
        FD_SET(tcp_fd, &readfds);
        FD_SET(udp_fd, &readfds);
        tv.tv_sec = TIMEOUT;
        tv.tv_usec = 0;

        int ret = select(max_fd + 1, &readfds, NULL, NULL, &tv);
        if(ret == -1)
        {
            perror("select");
            break;
        }
        else if(!ret)
        {
            printf("Время ожидания клиентов вышло\n");
            continue;
        }

        if(stop)
            break;

        if(FD_ISSET(tcp_fd, &readfds))
        {
            if(work_with_client_tcp(tcp_fd) == -1)
                break;
        }
        if(FD_ISSET(udp_fd, &readfds))
        {
            if(work_with_client_udp(udp_fd) == -1)
                break;
        }
    }
}