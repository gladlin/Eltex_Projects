#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LEN 128
#define MAX_ARGS 10

int start_execute(char *command);
int execute_program(char input_command[MAX_LEN]);