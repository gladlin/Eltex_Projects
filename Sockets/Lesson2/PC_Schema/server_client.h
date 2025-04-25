#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <stddef.h>
#include <errno.h>
#include <mqueue.h>

#define MQ_NAME "/clients"
#define PORT 5234
#define BUF_SIZE 256
#define MAX_CLIENTS 10
#define START_COUNT_SERVERS 2

#endif