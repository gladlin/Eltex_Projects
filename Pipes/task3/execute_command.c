#include "bash.h"

int execute_command(char *command)
{
    char *args[MAX_ARGS];
    int i = 0;
    char *token = strtok(command, " ");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (i == 0)
    {
        perror("Неверно введена команда");
        exit(EXIT_FAILURE);
    }

    int ret = execvp(args[0], args);
    if (ret == -1)
    {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    return 0;
}