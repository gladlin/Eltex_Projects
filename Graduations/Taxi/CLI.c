#include "taxi.h"

int count_drivers = 0;
int capacity = 5;
struct driver *drivers;
pid_t pid_of_cli;
struct command *command_memory;
struct command *answer_memory;

int main()
{
    pid_of_cli = getpid();

    int command_fd = shm_open(SHM_COMMAND, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(command_fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    if(ftruncate(command_fd, sizeof(struct command)) == -1)
    {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    command_memory = (struct command *)mmap(NULL, sizeof(struct command), PROT_READ | PROT_WRITE, MAP_SHARED, command_fd, 0);
    if(command_memory == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    int answer_fd = shm_open(SHM_ANSWER, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(answer_fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    if(ftruncate(answer_fd, sizeof(struct command)) == -1)
    {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    answer_memory = (struct command *)mmap(NULL, sizeof(struct command), PROT_READ | PROT_WRITE, MAP_SHARED, answer_fd, 0);
    if(answer_memory == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    drivers = calloc(capacity, sizeof(struct driver));
    if(drivers == NULL)
    {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    handle_input();

    
    free(drivers);
    munmap(command_memory, sizeof(struct command));
    close(command_fd);
    shm_unlink(SHM_COMMAND);
    
    munmap(answer_memory, sizeof(struct command));
    close(answer_fd);
    shm_unlink(SHM_ANSWER);
}