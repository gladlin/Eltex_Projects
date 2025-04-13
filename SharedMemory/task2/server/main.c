#include "../chat.h"
#include <string.h>

char users[MAX_USERS][MAX_USERNAME];
int user_count = 0;
//pthread_mutex_t user_mutex = PTHREAD_MUTEX_INITIALIZER;


int main()
{
    start_server();
    
    return 0;
}

int start_server()
{
    int shm_user_fd, shm_message_fd;
    if ((shm_user_fd = shm_open(SHM_USER, O_CREAT | O_RDWR, 0666)) == -1)
    {
        perror("shm_user_open server");
        exit(1);
    }

    if ((shm_message_fd = shm_open(SHM_MESSAGE, O_CREAT | O_RDWR, 0666)) == -1)
    {
        perror("shm_message_fd server");
        exit(1);
    }

    if (ftruncate(shm_user_fd, MAX_USERNAME) == -1)
    {
        perror("ftruncate shm_user_fd server");
        exit(1);
    }

    if (ftruncate(shm_message_fd, sizeof(struct message) * MAX_MESSAGES) == -1)
    {
        perror("ftruncate shm_message_fd server");
        exit(1);
    }

    char *shm_base_username = mmap(NULL, MAX_USERNAME, PROT_READ | PROT_WRITE, MAP_SHARED, shm_user_fd, 0);
    if (shm_base_username == MAP_FAILED)
    {
        perror("mmap shm_base_username server");
        exit(1);
    }

    struct message *shm_base_message = mmap(NULL, sizeof(struct message) * MAX_MESSAGES, PROT_READ | PROT_WRITE, MAP_SHARED, shm_message_fd, 0);
    if (shm_base_message == MAP_FAILED)
    {
        perror("mmap shm_base_message server");
        exit(1);
    }

    memset(shm_base_message, 0, sizeof(struct message) * MAX_MESSAGES);
    memset(shm_base_username, 0, MAX_USERNAME);

    start_thread(shm_base_username, shm_base_message);

    munmap(shm_base_username, MAX_USERNAME);
    munmap(shm_base_message, sizeof(struct message) * MAX_MESSAGES);
    close(shm_user_fd);
    close(shm_message_fd);
    shm_unlink(SHM_MESSAGE);
    shm_unlink(SHM_USER);
    /*shmdt(shm_base_message);
    shmdt(shm_base_username);
    shmctl(shm_id_message, IPC_RMID, NULL);
    shmctl(shm_id_username, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);*/
    return 0;
}

int start_thread(char *shm_base_username, struct message *shm_base_message)
{
    pthread_t thread_user, thread_message;

    int res_user = pthread_create(&thread_user, NULL, watch_users, (void *)shm_base_username);
    if (res_user != 0)
    {
        perror("Ошибка создания потока thread_user");
        exit(1);
    }

    int res_message = pthread_create(&thread_message, NULL, watch_messages, (void *)shm_base_message);
    if (res_message != 0)
    {
        perror("Ошибка создания потока thread_message");
        exit(1);
    }

    if (pthread_join(thread_message, NULL) != 0)
    {
        perror("pthread_join thread_message");
        exit(1);
    }
    printf("i am here");

    pthread_cancel(thread_user);
    printf("i am here");

    if (pthread_join(thread_user, NULL) != 0)
    {
        perror("pthread_join thread_user");
        exit(1);
    }
    return 0;
}

void *watch_users(void *arg)
{
    char message[MAX_LENGHT_MESSAGE] = "";
    char *shm_base_user = (char *)arg;

    sem_t *sem_messages = sem_open("/messages_count", O_CREAT, 0666, 0);
    if (sem_messages == SEM_FAILED)
    {
        perror("sem_open messages_count");
        pthread_exit(NULL);
    }

    while (1)
    {
        if (strcmp(shm_base_user, "") == 0 || strcmp(shm_base_user, "\n") == 0)
            continue;

        int already_exists = 0;
        for (int i = 0; i < user_count; ++i) {
            if (strcmp(users[i], shm_base_user) == 0) {
                already_exists = 1;
                break;
            }
        }

        if (!already_exists) {

            if (user_count < MAX_USERS)
            {
                strcpy(users[user_count], shm_base_user);
                user_count++;
                snprintf(message, MAX_LENGHT_MESSAGE, "В чат присоединился %s", shm_base_user);
                struct message newMessage;
                strcpy(newMessage.username, "system message");
                strcpy(newMessage.message, message);
                send_messages(newMessage);
            }
        }
    }

    sem_close(sem_messages);
    sem_unlink("/messages_count");
    return NULL;
}

void *watch_messages(void *arg)
{
    struct message *shm_base_message = (struct message *)arg;

    sem_t *sem_messages = sem_open("/messages_count", O_RDWR);
    if (sem_messages == SEM_FAILED)
    {
        perror("sem_open messages_count");
        pthread_exit(NULL);
    }

    int sem_value;
    int last_seen = 0;

    while (1)
    {
        sem_getvalue(sem_messages, &sem_value);
        if (last_seen < sem_value)
        {
            struct message msg = shm_base_message[last_seen];
            
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

                    printf("Сервер: Пользователь %s отключился, осталось пользователей: %d\n", msg.username, user_count);
                }

                if (user_count == 0)
                {
                    printf("Сервер: Все пользователи отключились, завершаю работу\n");
                    sem_unlink("/messages_count");
                    printf("пытаюсь завершить работу");
                    break;
                }
            }
            last_seen++;

            if (last_seen >= MAX_MESSAGES)
                last_seen = 0;
        }

        else
            usleep(100000);
    }

    sem_close(sem_messages);
    return NULL;
}

int send_messages(struct message newMessage)
{
    struct message *shm_base_message;
    int shm_message_fd;

    if ((shm_message_fd = shm_open(SHM_MESSAGE, O_RDWR, 0666)) == -1)
    {
        perror("shm_message_fd server");
        exit(1);
    }
    shm_base_message = mmap(NULL, sizeof(struct message) * MAX_MESSAGES, PROT_READ | PROT_WRITE, MAP_SHARED, shm_message_fd, 0);

    if (shm_base_message == MAP_FAILED)
    {
        perror("mmap send_messages");
        exit(1);
    }

    sem_t *sem_messages = sem_open("/messages_count", O_RDWR);
    if (sem_messages == SEM_FAILED)
    {
        perror("sem_open messages_count");
        exit(1);
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

    shm_base_message[sem_value] = newMessage;
    sem_post(sem_messages);

    munmap(shm_base_message, sizeof(struct message) * MAX_MESSAGES);
    close(shm_message_fd);
    sem_close(sem_messages);
    return 0;
}