#include "taxi.h"

struct driver *common_driver;

void handle_siguser1()
{
    extern struct command  *command_memory;
    extern struct command  *answer_memory;

    extern pid_t pid_of_cli;

    if (command_memory->driver == common_driver->driver_pid)
    {
        if (common_driver->time_left == 0)
            common_driver->time_left = command_memory->time;

        struct command answer = {common_driver->driver_pid, common_driver->time_left};
        memcpy(answer_memory, &answer, sizeof(struct command));

        kill(pid_of_cli, SIGUSR1);
    }
}

void driver_life(struct driver *current_driver)
{
    common_driver = current_driver;
    sigset_t sig_mask;
    if(sigemptyset(&sig_mask) == -1)
    {
        perror("sigemptyset");
        return;
    }
    if(sigaddset(&sig_mask, SIGUSR1) == -1)
    {
        
        perror("sigaddset");
        return;
    }

    int signal_fd = signalfd(-1, &(sig_mask), 0);
    if(signal_fd == -1)
    {
        perror("signalfd");
        return;
    }

    int epoll_fd = epoll_create(1);
    if(epoll_fd == -1)
    {
        perror("epoll_create");
        return;
    }

    struct epoll_event new_event;
    new_event.events = EPOLLIN;
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, signal_fd, &new_event) == -1)
    {
        perror("epoll_ctl");
        return;
    }

    // epoll_pwait(epoll_fd, &new_event, 1, 100000, ) нужно проставить маску как-то

    while(1)
    {
        if (pause() == -1 && errno == EINTR)
        {
            while (current_driver->time_left > 0)
            {
                current_driver->time_left = (time_t)sleep((unsigned int)current_driver->time_left);
            }
        }
    }
}