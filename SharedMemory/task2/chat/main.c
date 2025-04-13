#include "../chat.h"

int flag_is_connected = 1;
struct message *shm_base_message;

int main()
{
    connectToChat();
    return 0;
}

int connectToChat()
{
    int shm_user_fd;
    if((shm_user_fd = shm_open(SHM_USER,  O_RDWR, 0666)) == -1)
    {
        perror("shm_user_open client");
        exit(1);
    }

    char *shm_base_username = mmap(NULL, MAX_USERNAME, PROT_READ | PROT_WRITE, MAP_SHARED, shm_user_fd, 0);
    if (shm_base_username == MAP_FAILED) {
        perror("mmap shm_base_username client");
        exit(1);
    }

    printf("Введите свое имя, чтобы присоединится к чату: ");
    char username[MAX_USERNAME];

    fgets(username, MAX_USERNAME, stdin);
    if(username == NULL)
    {
        printf("Введенное имя должно быть менее 32-х символов");
        exit(1);
    }
    username[strcspn(username, "\n")] = '\0';

    sem_t *sem_clients = sem_open("/chat_clients", O_RDWR);
    if (sem_clients == SEM_FAILED) {
        perror("sem_open chat_clients");
        exit(1);
    }

    strcpy(shm_base_username, username);
    if (sem_post(sem_clients) == -1)
    {
        perror("sem_post chat_clients");
        exit(1);
    }

    start_thread_client(username);

    strcpy(shm_base_username, "");

    sem_close(sem_clients);
    munmap(shm_base_username, MAX_USERNAME);
    close(shm_user_fd);
    return 0;
}

int start_thread_client(char *username)
{
    pthread_t thread_get, thread_send;

    int res_get = pthread_create(&thread_get, NULL, getMessages, NULL);
    if(res_get != 0)
    {
        perror("Ошибка создания потока thread_get");
        exit(1);
    }

    int res_send  = pthread_create(&thread_send, NULL, sendMessage, (void *)username);
    if(res_send  != 0)
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
    if (sem_messages == SEM_FAILED) {
        perror("messages_count getMessages");
        return NULL;
    }

    int sem_value;
    int last_seen = 0;

    struct message newMessage;

    int shm_fd = shm_open(SHM_MESSAGE, O_RDWR, 0666);
    shm_base_message = mmap(NULL, sizeof(struct message) * MAX_MESSAGES, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);


    while(flag_is_connected == 1)
    {
        sem_getvalue(sem_messages, &sem_value);
        if(last_seen < sem_value)
        {
            newMessage = shm_base_message[last_seen];
            if(strcmp(newMessage.username, "system message") == 0)
                printf("%s\n", newMessage.message);
            else if (strcmp(newMessage.message, "exit") == 0)
                printf("Пользователь %s покинул чат\n", newMessage.username);
            else
                printf("%s: %s\n", newMessage.username, newMessage.message);
            last_seen++;
        }
        else
            usleep(100000);
    }
    
    printf("I am here get");
    return NULL;
}

void *sendMessage(void *arg)
{
    char *username = (char *)arg;
    char message[MAX_LENGHT_MESSAGE];

    while(1)
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
            break;
        }
    }

    return NULL;
}

int send_messages(struct message newMessage)
{
    struct message *shm_base_message;
    int shm_message_fd;

    if((shm_message_fd = shm_open(SHM_MESSAGE, O_CREAT | O_RDWR, 0666)) == -1)
    {
        perror("shm_message_fd server");
        exit(1);
    }
    shm_base_message = mmap(NULL, sizeof(struct message) * MAX_MESSAGES, PROT_READ | PROT_WRITE, MAP_SHARED, shm_message_fd, 0);

    if (shm_base_message == MAP_FAILED) {
        perror("mmap send_messages");
        exit(1);
    }

    sem_t *sem_messages = sem_open("/messages_count", O_RDWR, 0666, 0);
    if (sem_messages == SEM_FAILED) 
    {
        perror("sem_open messages_count");
        exit(1);
    }
    
    int sem_value;
    sem_getvalue(sem_messages, &sem_value);

    if(sem_value > MAX_MESSAGES)
    {
        printf("Достигнуто максимальное количество сообщений");
        exit(1);
    }

    shm_base_message[sem_value] = newMessage;
    sem_post(sem_messages);

    munmap(shm_base_message, sizeof(struct message) * MAX_MESSAGES);
    close(shm_message_fd);
    sem_close(sem_messages);

    return 0;
}