#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>

#define MY_SOCK_PATH "af_local_thread"
#define BACKLOG 5
#define SIZE_OF_BUF 32