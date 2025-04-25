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

#define BUF_SIZE 64