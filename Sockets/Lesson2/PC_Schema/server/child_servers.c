#include "server.h"

void *child_server(void *arg) 
{
    printf("Создан сервер\n");
    struct server *current_server = (struct server *)arg;

    mqd_t client_mq = mq_open(MQ_NAME, O_RDWR);
    if (client_mq == (mqd_t)-1) 
    {
        perror("mq_open child server");
        pthread_exit(NULL);
    }

    struct sockaddr_in server_addr;
    create_socket(&current_server->server_fd, &server_addr, current_server->port);

    char buf[BUF_SIZE];
    unsigned int prio;
    struct sockaddr_in client_addr;
    socklen_t client_size = sizeof(client_addr);

    struct timespec timeout = {.tv_sec = 5, .tv_nsec = 0};

    while (!stop) 
    {
        int size = mq_timedreceive(client_mq, (char*)&client_addr, sizeof(client_addr), &prio, &timeout);
        if (size == -1) {
            if (errno == ETIMEDOUT) {
                current_server->waiting_time += 5;
                continue;
            }
            perror("mq_timedreceive");
            break;
        }

        current_server->is_busy = 1;

        snprintf(buf, BUF_SIZE, "%d", current_server->port);
        if(sendto(current_server->server_fd, buf, BUF_SIZE, 0, (struct sockaddr*)&client_addr, client_size) == -1)
        {
            perror("sendto server 1");
            break;
        }

        if(recvfrom(current_server->server_fd, buf, BUF_SIZE, 0, (struct sockaddr*)&client_addr, &client_size) == -1)
        {
            perror("recvfrom server");
            break;
        }

        if (strcmp(buf, "Запрос на время\n") == 0) 
        {
            time_t now = time(NULL);
            struct tm *local = localtime(&now);
            snprintf(buf, BUF_SIZE, "Time: %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
        } else 
            snprintf(buf, BUF_SIZE, "Неверная команда");

        if(sendto(current_server->server_fd, buf, BUF_SIZE, 0, (struct sockaddr*)&client_addr, client_size) == -1)
        {
            perror("sendto server 2");
            break;
        }
        printf("Сервер отправил сообщение клиенту: %s", buf);

        current_server->is_busy = 0;
        timeout.tv_sec = 5;
        timeout.tv_nsec = 0;
    }

    mq_close(client_mq);
    pthread_exit(NULL);
}