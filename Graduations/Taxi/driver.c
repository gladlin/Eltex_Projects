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
    sigemptyset(&sig_mask);
    sigaddset(&sig_mask, SIGUSR1);

    int signal_fd = signalfd(-1, &sig_mask, 0);
    if (signal_fd == -1) 
    {
        perror("signalfd");
        return;
    }

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) 
    {
        perror("epoll_create1");
        return;
    }

    struct epoll_event new_event = { .events = EPOLLIN, .data.fd = signal_fd };

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, signal_fd, &new_event) == -1) 
    {
        perror("epoll_ctl");
        return;
    }

    while (1) 
    {
        struct epoll_event event;
        int nfds = epoll_pwait(epoll_fd, &event, 1, -1, NULL);
        if (nfds == -1) 
        {
            perror("epoll_pwait");
            break;
        }

        if (event.data.fd == signal_fd) 
        {
            struct signalfd_siginfo fdsi;
            ssize_t s = read(signal_fd, &fdsi, sizeof(fdsi));
            if (s != sizeof(fdsi)) 
            {
                perror("read");
                continue;
            }

            if (fdsi.ssi_signo == SIGUSR1)
                handle_siguser1();
                
            while (current_driver->time_left > 0)
            {
                current_driver->time_left = sleep((unsigned int)current_driver->time_left); // не возвращается если прилетел сигнал, так как мы заблокировали его
                // в любом случае должно вернутся сколько у нас времени осталось
                handle_siguser1();
                // может быть проблема в том, что он записывает все два раза, как будто два сигнала пришло. ПЕрвый он воспринимает как send_task, 
                // а второй как будто это просто ожидание завершения, и сигнал уже не придет еще раз, поэтому и происходит зависание
            }
        }
    }

    close(signal_fd);
    close(epoll_fd);
}