#include "../chat.h"

int main()
{
    start_server();
    return 0;
}

int start_server()
{
    int shm_user_fd, shm_message_fd;
    if((shm_user_fd = shm_open(SHM_USER, O_CREAT | O_RDWR, 0666)) == -1)
    {
        perror("shm_user_open server");
        exit(1);
    }

    if((shm_message_fd = shm_open(SHM_MESSAGE, O_CREAT | O_RDWR, 0666)) == -1)
    {
        perror("shm_message_fd server");
        exit(1);
    }

    if(ftruncate(shm_user_fd, MAX_USERNAME) == -1)
    {
        perror("ftruncate shm_user_fd server");
        exit(1);
    }

    if(ftruncate(shm_message_fd, sizeof(struct message) * MAX_MESSAGES) == -1)
    {
        perror("ftruncate shm_message_fd server");
        exit(1);
    }

    char *shm_base_username = mmap(NULL, MAX_USERNAME, PROT_READ | PROT_WRITE, MAP_SHARED, shm_user_fd, 0);
    if (shm_base_username == MAP_FAILED) {
        perror("mmap shm_base_username server");
        exit(1);
    }

    struct message *shm_base_message = mmap(NULL, sizeof(struct message) * MAX_MESSAGES, PROT_READ | PROT_WRITE, MAP_SHARED, shm_message_fd, 0);
    if (shm_base_message == MAP_FAILED) {
        perror("mmap shm_base_message server");
        exit(1);
    }

    memset(shm_base_message, 0, sizeof(struct message) * MAX_MESSAGES);
    memset(shm_base_username, 0, MAX_USERNAME);

    start_thread(shm_base_username);

    shm_unlink(SHM_MESSAGE);
    shm_unlink(SHM_USER);
    return 0;
}

int start_thread(char *shm_base_username)
{
    pthread_t thread_user;

    int res = pthread_create(&thread_user, NULL, watch_users, (void *)shm_base_username);
    if(res != 0)
    {
        perror("Ошибка создания потока thread_user");
        exit(1);
    }

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
    char users[MAX_USERS][MAX_LENGHT_MESSAGE];
    
    char *shm_base_user = (char *)arg;

    sem_t *sem_clients = sem_open("/chat_clients", O_CREAT, 0666, 0);
    if (sem_clients == SEM_FAILED) 
    {
        perror("sem_open chat_clients");
        pthread_exit(NULL);
    }

    sem_t *sem_messages = sem_open("/messages_count", O_CREAT, 0666, 0);
    if (sem_messages == SEM_FAILED) 
    {
        perror("sem_open messages_count");
        pthread_exit(NULL);
    }

    int i = 0;
    int clients;

    while (1) {
        sem_wait(sem_clients);
        sem_getvalue(sem_clients, &clients);

        if(clients == 0)
            break;

        if (strcmp(shm_base_user, "") == 0) {
            continue;
        }
    
        strcpy(users[i], shm_base_user);
        i++;

        snprintf(message, MAX_LENGHT_MESSAGE, "В чат присоединился %s", shm_base_user);

        struct message newMessage;
        strcpy(newMessage.username, "system message");
        strcpy(newMessage.message, message);

        send_messages(newMessage);

    }

    sem_close(sem_clients);
    sem_close(sem_messages);
    sem_unlink("/chat_clients");
    sem_unlink("/messages_count");
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