#include "server.h"

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
        pthread_cancel(thread_user);
        pthread_join(thread_user, NULL);
        exit(1);
    }

    if (pthread_join(thread_message, NULL) != 0)
    {
        perror("pthread_join thread_message");
        exit(1);
    }

    server_running = 0;

    if (pthread_join(thread_user, NULL) != 0)
    {
        perror("pthread_join thread_user");
        exit(1);
    }
    return 0;
}