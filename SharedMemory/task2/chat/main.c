#include "../chat.h"

int flag_is_connected = 1;
struct message *shm_base_message;

int main()
{
    connectToChat();
    exit(0);
}

int connectToChat()
{
    int shm_user_fd;
    if ((shm_user_fd = shm_open(SHM_USER, O_RDWR, 0666)) == -1)
    {
        perror("shm_user_open client");
        exit(1);
    }

    char *shm_base_username = mmap(NULL, MAX_USERNAME, PROT_READ | PROT_WRITE, MAP_SHARED, shm_user_fd, 0);
    if (shm_base_username == MAP_FAILED)
    {
        perror("mmap shm_base_username client");
        exit(1);
    }

    printf("Введите свое имя, чтобы присоединиться к чату: ");
    char username[MAX_USERNAME];

    if (fgets(username, MAX_USERNAME, stdin) == NULL)
    {
        printf("Ошибка ввода имени\n");
        exit(1);
    }
    username[strcspn(username, "\n")] = '\0';

    if (strlen(username) >= MAX_USERNAME)
    {
        printf("Имя должно быть короче %d символов\n", MAX_USERNAME);
        exit(1);
    }

    strcpy(shm_base_username, username);
    usleep(500000);
    memset(shm_base_username, 0, MAX_USERNAME);

    start_thread_client(username);

    munmap(shm_base_username, MAX_USERNAME);
    close(shm_user_fd);
    return 0;
}

int start_thread_client(char *username)
{
    pthread_t thread_get, thread_send;

    int res_get = pthread_create(&thread_get, NULL, getMessages, (void *)username);
    if (res_get != 0)
    {
        perror("Ошибка создания потока thread_get");
        exit(1);
    }

    int res_send = pthread_create(&thread_send, NULL, sendMessage, (void *)username);
    if (res_send != 0)
    {
        perror("Ошибка создания потока thread_send");
        exit(1);
    }

    if (pthread_join(thread_send, NULL) != 0)
    {
        perror("pthread_join thread_send");
        exit(1);
    }

    pthread_cancel(thread_get);

    if (pthread_join(thread_get, NULL) != 0)
    {
        perror("pthread_join thread_get");
        exit(1);
    }
    return 0;
}

void *getMessages()
{
    extern struct message *shm_base_message;

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
    shm_base_message = mmap(NULL, sizeof(struct message) * MAX_MESSAGES, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_base_message == MAP_FAILED)
    {
        perror("mmap shm_base_message getMessages");
        return NULL;
    }

    while (flag_is_connected == 1)
    {
        sem_getvalue(sem_messages, &sem_value);
        if (last_seen < sem_value)
        {
            newMessage = shm_base_message[last_seen];
            if (strcmp(newMessage.username, "system message") == 0)
                printf("%s\n", newMessage.message);
            else if (strcmp(newMessage.message, "exit") == 0)
                printf("Пользователь %s покинул чат\n", newMessage.username);
            else
                printf("%s: %s\n", newMessage.username, newMessage.message);
            last_seen++;
        }
        else
        {
            usleep(100000);
        }
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
        if (fgets(message, MAX_LENGHT_MESSAGE, stdin) == NULL)
        {
            perror("Ошибка ввода сообщения");
            break;
        }
        message[strcspn(message, "\n")] = '\0';

        struct message newMessage;
        strcpy(newMessage.username, username);
        strcpy(newMessage.message, message);

        send_messages(newMessage);

        if (strcmp(message, "exit") == 0)
        {
            flag_is_connected = 0;
            pthread_cancel(pthread_self());
            break;
        }
    }

    return NULL;
}

int send_messages(struct message newMessage)
{
    struct message *shm_base_message;
    int shm_message_fd;

    if ((shm_message_fd = shm_open(SHM_MESSAGE, O_RDWR, 0666)) == -1)
    {
        perror("shm_message_fd client");
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

    int index = sem_value % MAX_MESSAGES;
    shm_base_message[index] = newMessage;
    sem_post(sem_messages);

    munmap(shm_base_message, sizeof(struct message) * MAX_MESSAGES);
    close(shm_message_fd);
    sem_close(sem_messages);

    return 0;
}