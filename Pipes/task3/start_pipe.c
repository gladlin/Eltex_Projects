#include "bash.h"

int start_pipe(int fd[2], char *command, int type)
{
    if (type == 0)
        dup2(fd[1], STDOUT_FILENO);
    else
        dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);

    int res = execute_command(command);
    if(res == EXIT_FAILURE)
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}