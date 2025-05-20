#include "taxi.h"

void handle_input()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = cli_handler_siguser1;
    if (sigaction(SIGUSR1, &sa, NULL) != 0)
    {
        perror("sigaction cli");
        return;
    }

    char message[BUF_SIZE] = "";
    while (strcmp(message, "exit") != 0)
    {
        printf("Ожидаю ввод команды: ");
        if (fgets(message, BUF_SIZE, stdin) == NULL)
        {
            perror("fgets Длина команды должна быть менее 64 символов");
            continue;
        }

        char *command = strtok(message, " \n");

        if (strcmp(command, "create_driver") == 0)
        {
            pid_t new_driver = create_driver();
            printf("Новый водитель имеет pid %d\n", new_driver);
        }
        else if (strcmp(command, "send_task") == 0)
        {
            char *pid = strtok(NULL, " ");
            char *task_timer = strtok(NULL, " ");

            if (pid != NULL && task_timer != NULL)
                send_task(pid, task_timer);
            else
                printf("Шаблон написания команды: send_task <pid> <task_timer>\n");
        }
        else if (strcmp(command, "get_status") == 0)
        {
            char *pid = strtok(NULL, " ");
            if (pid != NULL)
                get_status(pid);
            else
                printf("Шаблон написания команды: get_status <pid>\n");
        }
        else if (strcmp(command, "get_drivers") == 0)
            get_drivers();
        else if (strcmp(command, "exit") == 0)
            break;
        else
        {
            printf("Была введена неверная команда: '%s'\n", command ? command : "NULL");
            continue;
        }
    }
}

void cli_handler_siguser1()
{
   
}