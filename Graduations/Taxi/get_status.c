#include "taxi.h"

void get_status(char *pid)
{
    pid_t driver = (pid_t)strtol(pid, NULL, 10);
    
    time_t answer_from_driver = ask_driver(driver, 0);

    if(answer_from_driver == 0)
        printf("Process with PID %d is Avaible\n", driver);
    else if(answer_from_driver == (time_t)-1)
        printf("Error while waiting answer\n");
    else
        printf("Process with PID %d is Busy for %ld seconds\n", driver, answer_from_driver);
}
