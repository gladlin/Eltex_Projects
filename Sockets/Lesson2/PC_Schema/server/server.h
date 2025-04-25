#ifndef SERVER_H
#define SERVER_H

#include "../server_client.h"

extern volatile sig_atomic_t stop;

struct server {
    int port;
    int server_fd;
    int is_busy;
    int is_dynamic;
    time_t waiting_time;
};

int create_socket(int *fd, struct sockaddr_in *addr, int port);
void *child_server(void *arg);
int listen_server(mqd_t client_mq);
void handle_sigint();
void clear_all(mqd_t mq, pthread_t *threads, struct server *servers, int count);
int create_pool();
int manage_server_pool();

#endif