#include "server.h"
#include "../common/common.h"

void *watch_users(void *arg)
{
    static char (*shm_users)[MAX_USERNAME] = NULL;
    if (!shm_users) 
    {
        int fd = shm_open("/shm_users_list", O_RDWR, 0666);
        shm_users = mmap(NULL, sizeof(char[MAX_USERS][MAX_USERNAME]), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    }

    char message[MAX_LENGHT_MESSAGE] = "";
    char *shm_base_user = (char *)arg;

    sem_t *sem_messages = sem_open("/messages_count", O_RDWR);
    if (sem_messages == SEM_FAILED)
    {
        perror("sem_open messages_count watch_users");
        pthread_exit(NULL);
    }

    while (server_running)
    {
        if (strcmp(shm_base_user, "") == 0 || strcmp(shm_base_user, "\n") == 0)
        {
            usleep(100000);
            continue;
        }

        int already_exists = 0;
        for (int i = 0; i < user_count; ++i)
        {
            if (strcmp(users[i], shm_base_user) == 0)
            {
                already_exists = 1;
                break;
            }
        }

        if (!already_exists)
        {
            printf("%s\n", shm_base_user);
            if (user_count < MAX_USERS)
            {
                strcpy(users[user_count], shm_base_user);
                user_count++;
                strcpy(shm_users[user_count - 1], shm_base_user);
                update_user_list(users, user_count);
                snprintf(message, MAX_LENGHT_MESSAGE, "%s Joined the chat", shm_base_user);
                struct message newMessage;
                strcpy(newMessage.username, "system message");
                strcpy(newMessage.message, message);
                send_messages(newMessage);
            }
        }

        memset(shm_base_user, 0, MAX_USERNAME);
        usleep(100000);
    }

    sem_close(sem_messages);
    return NULL;
}

void *watch_messages(void *arg)
{
    static char (*shm_users)[MAX_USERNAME] = NULL;
    if (!shm_users) 
    {
        int fd = shm_open("/shm_users_list", O_RDWR, 0666);
        shm_users = mmap(NULL, sizeof(char[MAX_USERS][MAX_USERNAME]), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    }

    struct message *shm_base_message = (struct message *)arg;

    sem_t *sem_messages = sem_open("/messages_count", O_RDWR);
    if (sem_messages == SEM_FAILED)
    {
        perror("sem_open messages_count watch_messages");
        pthread_exit(NULL);
    }

    int sem_value;
    int last_seen = 0;

    while (server_running)
    {
        sem_getvalue(sem_messages, &sem_value);
        while (last_seen < sem_value)
        {
            int index = last_seen % MAX_MESSAGES;
            struct message msg = shm_base_message[index];

            if (strcmp(msg.message, "exit") == 0)
            {
                int user_index = -1;
                for (int i = 0; i < user_count; i++)
                {
                    if (strcmp(users[i], msg.username) == 0)
                    {
                        user_index = i;
                        break;
                    }
                }

                if (user_index != -1)
                {
                    for (int i = user_index; i < user_count - 1; i++)
                    {
                        strcpy(users[i], users[i + 1]);
                    }
                    user_count--;
                    memset(users[user_count], 0, MAX_USERNAME);
                    update_user_list(users, user_count);
                }
                memset(shm_users[user_count], 0, MAX_USERNAME);


                if (user_count == 0)
                {
                    server_running = 0;
                    break;
                }
            }
            last_seen++;
        }

        usleep(100000);
    }

    sem_close(sem_messages);
    return NULL;
}