#include "client.h"
#include "../common/common.h"

int start_thread_client(char *username)
{
    pthread_t thread_get, thread_send, thread_users;

    init_ui();
    int res_send = pthread_create(&thread_send, NULL, sendMessage, (void *)username);
    if (res_send != 0)
    {
        perror("Ошибка создания потока thread_send");
        exit(1);
    }

    int res_get = pthread_create(&thread_get, NULL, getMessages, (void *)username);
    if (res_get != 0)
    {
        perror("Ошибка создания потока thread_get");
        pthread_cancel(thread_send);
        pthread_join(thread_send, NULL);
        exit(1);
    }

    int res_users = pthread_create(&thread_users, NULL, getUserList, NULL);
    if (res_users != 0)
    {
        perror("Ошибка создания потока thread_users");
        pthread_cancel(thread_send);
        pthread_join(thread_send, NULL);
        pthread_cancel(thread_get);
        pthread_join(thread_get, NULL);
        exit(1);
    }

    if (pthread_join(thread_send, NULL) != 0)
    {
        perror("pthread_join thread_send");
        pthread_cancel(thread_send);
        pthread_join(thread_send, NULL);
        pthread_cancel(thread_users);
        pthread_join(thread_users, NULL);
        exit(1);
    }

    pthread_cancel(thread_get);

    if (pthread_join(thread_get, NULL) != 0)
    {
        perror("pthread_join thread_get");
        pthread_cancel(thread_users);
        pthread_join(thread_users, NULL);
        exit(1);
    }
    
    if (pthread_join(thread_users, NULL) != 0)
    {
        perror("pthread_join thread_users");
        exit(1);
    }
    cleanup_ui();
    return 0;
}