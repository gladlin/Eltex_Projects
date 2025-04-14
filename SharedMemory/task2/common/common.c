#include "common.h"

int send_messages(struct message newMessage)
{
    struct message *shm_base_message;
    int shm_message_fd;

    if ((shm_message_fd = shm_open(SHM_MESSAGE, O_RDWR, 0666)) == -1)
    {
        perror("shm_message_fd");
        return -1;
    }

    shm_base_message = mmap(NULL, sizeof(struct message) * MAX_MESSAGES, PROT_READ | PROT_WRITE, MAP_SHARED, shm_message_fd, 0);
    if (shm_base_message == MAP_FAILED)
    {
        perror("mmap send_messages");
        close(shm_message_fd);
        return -1;
    }

    sem_t *sem_messages = sem_open("/messages_count", O_RDWR);
    if (sem_messages == SEM_FAILED)
    {
        perror("sem_open messages_count");
        munmap(shm_base_message, sizeof(struct message) * MAX_MESSAGES);
        close(shm_message_fd);
        return -1;
    }

    int sem_value;
    sem_getvalue(sem_messages, &sem_value);

    if (sem_value >= MAX_MESSAGES)
    {
        printf("Достигнуто максимальное количество сообщений\n");
        munmap(shm_base_message, sizeof(struct message) * MAX_MESSAGES);
        close(shm_message_fd);
        sem_close(sem_messages);
        return -1;
    }

    int index = sem_value % MAX_MESSAGES;
    shm_base_message[index] = newMessage;
    sem_post(sem_messages);

    munmap(shm_base_message, sizeof(struct message) * MAX_MESSAGES);
    close(shm_message_fd);
    sem_close(sem_messages);
    return 0;
}