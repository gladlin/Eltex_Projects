#include "taxi.h"

void send_task(char *pid, char *task_timer)
{
    pid_t driver = (pid_t)strtol(pid, NULL, 10);
    time_t task_time_end = (time_t)strtol(task_timer, NULL, 10);
    
    time_t answer_from_driver = ask_driver(driver, task_time_end);
    printf("Kiss kidd goodbye\n");

    if(answer_from_driver == 0)
        printf("Task is send");
    else if(answer_from_driver == (time_t)-1)
        printf("Error while waiting answer");
    else
        printf("%d is Busy for %ld seconds", driver, answer_from_driver);     
}
