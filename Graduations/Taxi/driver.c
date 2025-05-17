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
    struct sigaction sa;
    sa.sa_handler = handle_siguser1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(sigaction(SIGUSR1, &sa, NULL) != 0)
    {
        perror("sigaction");
        return;
    }
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