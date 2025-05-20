#include "taxi.h"

struct driver *common_driver;

void driver_life(struct driver *current_driver) 
{
    int signal_fd, timer_fd, epoll_fd;

    init_driver_resources(current_driver, &signal_fd, &timer_fd, &epoll_fd);
    process_driver_events(signal_fd, timer_fd, epoll_fd);
    cleanup_driver_resources(signal_fd, timer_fd, epoll_fd);

    exit(EXIT_SUCCESS);
}

void init_driver_resources(struct driver *current_driver, int *signal_fd, int *timer_fd, int *epoll_fd) 
{
    common_driver = current_driver;
    common_driver->driver_pid = getpid();

    sigset_t sig_mask;
    sigemptyset(&sig_mask);
    sigaddset(&sig_mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sig_mask, NULL);

    *signal_fd = signalfd(-1, &sig_mask, 0);
    if (*signal_fd == -1) 
    {
        perror("signalfd");
        exit(EXIT_FAILURE);
    }

    *timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (*timer_fd == -1) 
    {
        perror("timerfd_create");
        close(*signal_fd);
        exit(EXIT_FAILURE);
    }

    *epoll_fd = epoll_create1(0);
    if (*epoll_fd == -1) 
    {
        perror("epoll_create1");
        close(*signal_fd);
        close(*timer_fd);
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = *signal_fd;
    if (epoll_ctl(*epoll_fd, EPOLL_CTL_ADD, *signal_fd, &ev) == -1) 
    {
        perror("epoll_ctl signalfd");
        close(*signal_fd);
        close(*timer_fd);
        close(*epoll_fd);
        exit(EXIT_FAILURE);
    }

    ev.data.fd = *timer_fd;
    if (epoll_ctl(*epoll_fd, EPOLL_CTL_ADD, *timer_fd, &ev) == -1) 
    {
        perror("epoll_ctl timerfd");
        close(*signal_fd);
        close(*timer_fd);
        close(*epoll_fd);
        exit(EXIT_FAILURE);
    }
}

void process_driver_events(int signal_fd, int timer_fd, int epoll_fd) 
{
    extern struct command *command_memory;
    extern struct command *answer_memory;
    extern pid_t pid_of_cli;

    struct epoll_event events[2];
    while (1) 
    {
        int nfds = epoll_wait(epoll_fd, events, 2, -1);
        if (nfds == -1) 
        {
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < nfds; i++) 
        {
            if (events[i].data.fd == signal_fd) 
            {
                struct signalfd_siginfo fdsi;
                if (read(signal_fd, &fdsi, sizeof(fdsi)) != sizeof(fdsi)) 
                {
                    perror("read signalfd");
                    continue;
                }

                if (fdsi.ssi_signo == SIGUSR1 && command_memory->driver == common_driver->driver_pid) 
                {
                    if (common_driver->time_left > 0) 
                    {
                        struct itimerspec ts;
                        if (timerfd_gettime(timer_fd, &ts) == -1)
                            perror("timerfd_gettime");
                        else
                            common_driver->time_left = ts.it_value.tv_sec;
                    }

                    if (common_driver->time_left == 0 && command_memory->time > 0) 
                    {
                        common_driver->time_left = command_memory->time;
                        struct itimerspec ts;
                        ts.it_value.tv_sec = common_driver->time_left;
                        ts.it_value.tv_nsec = 0;
                        ts.it_interval.tv_sec = 0;
                        ts.it_interval.tv_nsec = 0;
                        if (timerfd_settime(timer_fd, 0, &ts, NULL) == -1)
                            perror("timerfd_settime");
                    }

                    struct command answer = {common_driver->driver_pid, common_driver->time_left};
                    memcpy(answer_memory, &answer, sizeof(struct command));
                    if (kill(pid_of_cli, SIGUSR1) == -1)
                        perror("kill");
                }
            } 
            else if (events[i].data.fd == timer_fd) 
            {
                uint64_t exp;
                if (read(timer_fd, &exp, sizeof(exp)) != sizeof(exp)) 
                {
                    perror("read timerfd");
                    continue;
                }
                common_driver->time_left = 0;
            }
        }
    }
}

void cleanup_driver_resources(int signal_fd, int timer_fd, int epoll_fd) 
{
    close(signal_fd);
    close(timer_fd);
    close(epoll_fd);
}
