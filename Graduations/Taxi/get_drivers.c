#include "taxi.h"

void get_drivers()
{
    extern int count_drivers;
    extern struct driver *drivers;
    struct driver current_driver;

    for(int i = 0; i < count_drivers; i++)
    {
        current_driver = drivers[i];
        time_t answer_from_driver = ask_driver(current_driver.driver_pid, 0);
        if(answer_from_driver == 0)
            printf("Process with PID %d is Avaible\n", current_driver.driver_pid);
        else if(answer_from_driver == (time_t)-1)
            printf("Error while waiting answer\n");
        else
            printf("Process with PID %d is Busy for %ld seconds\n", current_driver.driver_pid, answer_from_driver);
    }
}
