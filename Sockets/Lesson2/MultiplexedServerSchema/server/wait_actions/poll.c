#include "../server.h"
#include <poll.h>

void wait_action(int tcp_fd, int udp_fd)
{
    struct pollfd fds[2];
	int ret;
	fds[0].fd = tcp_fd;
	fds[0].events = POLLIN;

    fds[1].fd = udp_fd;
	fds[1].events = POLLIN;

    while(!stop)
    {
        ret = poll(fds, 2, TIMEOUT * 1000);
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

        if (fds[0].revents &POLLIN)
        {
            if(work_with_client_tcp(tcp_fd) == -1)
                break;
        }
        if (fds[1].revents &POLLOUT)
        {
            if(work_with_client_udp(udp_fd) == -1)
                break;
        }
    }
}