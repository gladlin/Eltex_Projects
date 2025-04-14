#include "client.h"
#include "../common/common.h"

void *getMessages()
{
    sem_t *sem_messages = sem_open("/messages_count", O_RDWR);
    if (sem_messages == SEM_FAILED)
    {
        perror("messages_count getMessages");
        return NULL;
    }

    int sem_value;
    int last_seen = 0;

    struct message newMessage;

    int shm_fd = shm_open(SHM_MESSAGE, O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open SHM_MESSAGE getMessages");
        sem_close(sem_messages);
        return NULL;
    }

    shm_base_message = mmap(NULL, sizeof(struct message) * MAX_MESSAGES, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_base_message == MAP_FAILED)
    {
        perror("mmap shm_base_message getMessages");
        close(shm_fd);
        sem_close(sem_messages);
        return NULL;
    }

    while (flag_is_connected)
    {
        sem_getvalue(sem_messages, &sem_value);
        while (last_seen < sem_value)
        {
            int index = last_seen % MAX_MESSAGES;
            newMessage = shm_base_message[index];
            add_message(newMessage.username, newMessage.message);
            last_seen++;
        }
        usleep(100000);
    }

    munmap(shm_base_message, sizeof(struct message) * MAX_MESSAGES);
    close(shm_fd);
    sem_close(sem_messages);
    return NULL;
}

void *sendMessage(void *arg)
{
    char *username = (char *)arg;
    char message[MAX_LENGHT_MESSAGE];

    while (1)
    {
        get_input(message, sizeof(message));
        message[strcspn(message, "\n")] = '\0';
        if (strcmp(message, "") == 0)
            continue;

        struct message newMessage;
        strcpy(newMessage.username, username);
        strcpy(newMessage.message, message);

        send_messages(newMessage);

        if (strcmp(message, "exit") == 0)
        {
            flag_is_connected = 0;
            break;
        }
    }

    return NULL;
}

void *getUserList() {
    int shm_fd = shm_open("/shm_users_list", O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open users_list");
        return NULL;
    }

    char (*shm_users)[MAX_USERNAME] = mmap(NULL, sizeof(char[MAX_USERS][MAX_USERNAME]), PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_users == MAP_FAILED) {
        perror("mmap users_list");
        return NULL;
    }

    while (flag_is_connected) {
        int count = 0;
        for (int i = 0; i < MAX_USERS; ++i) {
            if (shm_users[i][0] != '\0') count++;
        }

        update_user_list(shm_users, count);
        usleep(300000);
    }

    munmap(shm_users, sizeof(char[MAX_USERS][MAX_USERNAME]));
    close(shm_fd);
    return NULL;
}
