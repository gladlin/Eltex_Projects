#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LEN 128
#define MAX_ARGS 10


int start_pipe(int fd[2], char *command, int type);
int execute_command(char *command);
int execute_pipeline(char input_command[MAX_LEN]);