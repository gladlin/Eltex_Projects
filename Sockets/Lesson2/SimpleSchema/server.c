#include "server_client.h"

#define BACKLOG 5

int server_fd;
pthread_t client_threads[BACKLOG];
int client_addresses[BACKLOG];
int thread_count = 0;


void *client_work(void *client_addr);
void handle_sigint();

int main()
{
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(sigaction(SIGINT, &sa, NULL) != 0)
    {
        perror("sigaction");
        exit(1);
    }

    struct sockaddr_in server;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1)
    {
        perror("socket server");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(3425);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("bind server");
        close(server_fd);
        exit(1);
    }
    if(listen(server_fd, BACKLOG) == -1)
    {
        perror("listen server");
        close(server_fd);
        exit(1);
    }
    
    while(thread_count < BACKLOG)
    {
        int client_fd = accept(server_fd, NULL, NULL);

        if(client_fd == -1)
        {
            perror("accept server");
            close(server_fd);
            exit(1);
        }
        
        client_addresses[thread_count] = client_fd;
        pthread_t thread;
        if(pthread_create(&thread, NULL, client_work, &client_addresses[thread_count]) == -1)
        {
            perror("accept server");
            close(server_fd);
            exit(1);
        }
        client_threads[thread_count] = thread;
        thread_count++;
    }
    handle_sigint();
    return 0;
}

void handle_sigint()
{
    close(server_fd);
    for(int i = 0; i < thread_count; i++)
    {
        if(pthread_join(client_threads[i], NULL) !=0 )
            perror("pthread_join server");
    }
}

void *client_work(void *client_addr)
{
    int client_fd = *(int *)client_addr;

    char buf[BUF_SIZE];
    if(recv(client_fd, buf, BUF_SIZE, 0) == -1)
    {
        perror("accept server");
        close(client_fd);
        return NULL;
    }

    if(strcmp(buf, "Запрос на время") != 0)
        strncpy(buf, "Неверная команда", BUF_SIZE);
    else
    {
        time_t mytime = time(NULL);
        struct tm *now = localtime(&mytime);
        if(snprintf(buf, BUF_SIZE, "Time: %d:%d:%d\n", now->tm_hour, now->tm_min, now->tm_sec) == 0)
        {
            perror("snprintf server");
            close(client_fd);
            return NULL;
        }
    }

    if(send(client_fd, buf, BUF_SIZE, 0) == -1)
    {
        perror("send server");
        close(client_fd);
        return NULL;
    }
    printf("\nСервер отправил время клиенту\n");
    close(client_fd);
    return NULL;
}