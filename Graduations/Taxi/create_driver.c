#include "taxi.h"

pid_t create_driver()
{
    extern int count_drivers;
    extern int capacity;
    extern struct driver *drivers;

    if(count_drivers == capacity)
    {
        capacity *= 2;
        drivers = realloc(drivers, capacity * sizeof(struct driver));
        if(drivers == NULL)
        {
            perror("realloc");
            return (pid_t)0;
        }
    }
    drivers[count_drivers].time_left = 0;
    int res = fork();
    if(res == 0)
    {
        pid_t child_pid = getpid();
        drivers[count_drivers].driver_pid = child_pid;
        driver_life(&drivers[count_drivers]);
    }
    else if(res == -1)
    {
        perror("fork");
        return (pid_t)-1;
    }
    else
    {
        drivers[count_drivers].driver_pid = res;
        count_drivers++;
    }
    
    return res;
}