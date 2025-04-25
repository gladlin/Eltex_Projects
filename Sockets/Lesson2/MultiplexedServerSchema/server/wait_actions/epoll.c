#include "../server.h"
#include <sys/epoll.h>
#include <unistd.h>

void wait_action(int tcp_fd, int udp_fd)
{
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
    {
        perror("epoll_create1");
        return;
    }

    struct epoll_event event_tcp = {.events = EPOLLIN, .data.fd = tcp_fd};
    struct epoll_event event_udp = {.events = EPOLLIN, .data.fd = udp_fd};

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, tcp_fd, &event_tcp) == -1)
    {
        perror("epoll_ctl tcp");
        close(epoll_fd);
        return;
    }

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, udp_fd, &event_udp) == -1)
    {
        perror("epoll_ctl udp");
        close(epoll_fd);
        return;
    }

    struct epoll_event events[2];

    while (!stop)
    {
        int n = epoll_wait(epoll_fd, events, 2, TIMEOUT * 1000);

        if (n == -1)
        {
            perror("epoll_wait");
            break;
        }
        else if (n == 0)
        {
            printf("Время ожидания клиентов вышло\n");
            continue;
        }

        for (int i = 0; i < n; i++)
        {
            if (events[i].data.fd == tcp_fd)
            {
                if (work_with_client_tcp(tcp_fd) == -1)
                    break;
            }
            else if (events[i].data.fd == udp_fd)
            {
                if (work_with_client_udp(udp_fd) == -1)
                    break;
            }
        }
    }
    close(epoll_fd);
}
