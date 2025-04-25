#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>

#define MY_SOCK_PATH_SERVER "af_local_dgram_S"
#define MY_SOCK_PATH_CLIENT "af_local_dgram_C"
#define BACKLOG 5
#define SIZE_OF_BUF 32