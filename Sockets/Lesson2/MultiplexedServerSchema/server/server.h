#ifndef SERVER_H
#define SERVER_H

#include <sys/select.h>
#include "../server_client.h"
#define BACKLOG 5
#define TIMEOUT 5

extern volatile sig_atomic_t stop;

void handler_sigint();
void start_server();
void wait_action(int tcp_fd, int udp_fd);
int create_socket_udp(int *fd, struct sockaddr_in *sock);
int create_tcp_socket(int *fd, struct sockaddr_in *sock);
int work_with_client_udp(int fd);
int work_with_client_tcp(int fd);

#endif