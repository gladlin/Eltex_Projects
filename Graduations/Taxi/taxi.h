#ifndef TAXI_H
#define TAXI_H

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define BUF_SIZE 64
#define SHM_COMMAND "/command_shm"
#define SHM_ANSWER "/answer_shm"

struct driver
{
    pid_t driver_pid;
    time_t time_left;
};

struct command
{
    pid_t driver;
    time_t time;
};

void send_task(char *pid, char *task_timer);
void handle_input();
void get_status(char *pid);
void get_drivers();
void handle_siguser1();
void driver_life(struct driver *current_driver);
pid_t create_driver();
time_t ask_driver(pid_t driver, time_t task_time_end);
void cli_handler_siguser1();

#endif