#include "taxi.h"

time_t ask_driver(pid_t driver, time_t task_time_end)
{
    extern struct command *command_memory;
    extern struct command *answer_memory;

    struct command new_command = { driver,  task_time_end };

    memcpy(command_memory, &new_command, sizeof(new_command));
    if(kill(driver, SIGUSR1) == -1)
        perror("kill");

    if(pause() == -1 && errno != EINTR)
    {
        perror("pause");
        return (time_t)-1;
    }

    return answer_memory->time;
}