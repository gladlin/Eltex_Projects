#ifndef SERVER_H
#define SERVER_H

#include "../server_client.h"

#define SERVERS_IN_POOL 3
#define BACKLOG 5
#define START_COUNT_SERVERS 2

struct server
{
    int port;
    int server_fd;
    int is_busy;
};

extern pthread_t threads[SERVERS_IN_POOL];
extern volatile sig_atomic_t stop;
extern struct server servers[SERVERS_IN_POOL];

int create_socket(int *fd, struct sockaddr_in *addr, int port);
void handle_sigint();
void listen_server(int listen_fd);
void *child_server(void *arg);

#endif