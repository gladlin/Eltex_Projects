#include "bash.h"

int execute_pipeline(char input_command[MAX_LEN])
{
    char *commands[2];
    commands[0] = strtok(input_command, "|");
    commands[1] = strtok(NULL, "|");
    
    int fd[2];
    pipe(fd); 

    pid_t pid = fork ();
    if (pid == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (pid == 0) 
    {
        if(start_pipe(fd, commands[0], 0) == EXIT_FAILURE)
            exit (EXIT_FAILURE);
    }
    else
    {
        pid_t pid1 = fork ();
        if (pid1 == -1)
        {
            perror("fork");
            return EXIT_FAILURE;
        }
        if (pid1 == 0) 
        {
            if(start_pipe(fd, commands[1], 1) == EXIT_FAILURE)
		        exit (EXIT_FAILURE);
        }
        else
        {
            close(fd[0]);
            close(fd[1]);
            int status;
            if (waitpid(pid1, &status, 0) == -1 || waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid");
                return EXIT_FAILURE;
            }
        }

    }
    return EXIT_SUCCESS; 
}