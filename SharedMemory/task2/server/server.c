#include "server.h"

char users[MAX_USERS][MAX_USERNAME];
int user_count = 0;
int server_running = 1;

int main()
{
    start_server();
    return 0;
}

int start_server()
{
    sem_t *sem_messages;

    sem_messages = sem_open("/messages_count", O_CREAT | O_RDWR, 0666, 0);
    if (sem_messages == SEM_FAILED)
    {
        perror("sem_open messages_count init");
        exit(1);
    }

    int shm_users_fd = shm_open("/shm_users_list", O_CREAT | O_RDWR, 0666);
    if (shm_users_fd == -1) 
    {
        perror("shm_open shm_users_list");
        exit(1);
    }

    if (ftruncate(shm_users_fd, sizeof(char[MAX_USERS][MAX_USERNAME])) == -1)
    {
        perror("ftruncate shm_users_fd server");
        close(shm_users_fd);
        sem_close(sem_messages);
        sem_unlink("/messages_count");
    }

    char (*shm_users)[MAX_USERNAME] = mmap(NULL, sizeof(char[MAX_USERS][MAX_USERNAME]), PROT_READ | PROT_WRITE, MAP_SHARED, shm_users_fd, 0);
    if (shm_users == MAP_FAILED)
    {
        perror("mmap shm_base_username server");
        close(shm_users_fd);
        shm_unlink(SHM_USER);
        exit(1);
    }
    memset(shm_users, 0, sizeof(char[MAX_USERS][MAX_USERNAME]));


    int shm_user_fd, shm_message_fd;
    if ((shm_user_fd = shm_open(SHM_USER, O_CREAT | O_RDWR, 0666)) == -1)
    {
        perror("shm_user_open server");
        sem_close(sem_messages);
        sem_unlink("/messages_count");
        exit(1);
    }

    if ((shm_message_fd = shm_open(SHM_MESSAGE, O_CREAT | O_RDWR, 0666)) == -1)
    {
        perror("shm_message_fd server");
        close(shm_user_fd);
        shm_unlink(SHM_USER);
        sem_close(sem_messages);
        sem_unlink("/messages_count");
        exit(1);
    }

    if (ftruncate(shm_user_fd, MAX_USERNAME) == -1)
    {
        perror("ftruncate shm_user_fd server");
        close(shm_user_fd);
        close(shm_message_fd);
        shm_unlink(SHM_USER);
        shm_unlink(SHM_MESSAGE);
        sem_close(sem_messages);
        sem_unlink("/messages_count");
        exit(1);
    }

    if (ftruncate(shm_message_fd, sizeof(struct message) * MAX_MESSAGES) == -1)
    {
        perror("ftruncate shm_message_fd server");
        close(shm_user_fd);
        close(shm_message_fd);
        shm_unlink(SHM_USER);
        shm_unlink(SHM_MESSAGE);
        sem_close(sem_messages);
        sem_unlink("/messages_count");
        exit(1);
    }

    char *shm_base_username = mmap(NULL, MAX_USERNAME, PROT_READ | PROT_WRITE, MAP_SHARED, shm_user_fd, 0);
    if (shm_base_username == MAP_FAILED)
    {
        perror("mmap shm_base_username server");
        close(shm_user_fd);
        close(shm_message_fd);
        shm_unlink(SHM_USER);
        shm_unlink(SHM_MESSAGE);
        sem_close(sem_messages);
        sem_unlink("/messages_count");
        exit(1);
    }

    struct message *shm_base_message = mmap(NULL, sizeof(struct message) * MAX_MESSAGES, PROT_READ | PROT_WRITE, MAP_SHARED, shm_message_fd, 0);
    if (shm_base_message == MAP_FAILED)
    {
        perror("mmap shm_base_message server");
        munmap(shm_base_username, MAX_USERNAME);
        close(shm_user_fd);
        close(shm_message_fd);
        shm_unlink(SHM_USER);
        shm_unlink(SHM_MESSAGE);
        sem_close(sem_messages);
        sem_unlink("/messages_count");
        exit(1);
    }

    memset(shm_base_message, 0, sizeof(struct message) * MAX_MESSAGES);
    memset(shm_base_username, 0, MAX_USERNAME);

    start_thread(shm_base_username, shm_base_message);

    munmap(shm_base_username, MAX_USERNAME);
    munmap(shm_base_message, sizeof(struct message) * MAX_MESSAGES);
    munmap(shm_users, sizeof(char[MAX_USERS][MAX_USERNAME]));
    close(shm_user_fd);
    close(shm_message_fd);
    close(shm_users_fd);
    shm_unlink(SHM_MESSAGE);
    shm_unlink(SHM_USER);
    shm_unlink("/shm_users_list");
    sem_close(sem_messages);
    sem_unlink("/messages_count");

    return 0;
}