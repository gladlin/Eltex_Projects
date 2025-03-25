#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int waitForProcess(pid_t pid, int number);
int createManyProcess();
void process1();
void process2();