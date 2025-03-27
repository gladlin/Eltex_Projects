#include "bash.h"

int execute_program(char input_command[MAX_LEN])
{
    //char *first_command = strtok(input_command, "|");

    pid_t pid = fork ();
    if (pid == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (!pid) 
    {
        int res = start_execute(input_command);
        if(res == EXIT_FAILURE)
		    exit (EXIT_FAILURE);
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return EXIT_FAILURE;
        }
        //char *second_command = strtok(input_command, "|");
    }
    return EXIT_SUCCESS;
    
}

int start_execute(char *command)
{
    char *name_command = strtok(command, " ");
    
    char *args[MAX_ARGS];
    args[0] = name_command;

    int i = 1;
    while(args != NULL && i < MAX_ARGS - 2)
    {
        args[i] = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;

    int ret = execvp(name_command, args);
    if (ret == -1) {
		perror ("execv");
		exit (EXIT_FAILURE);
	}
    return 0;
}