#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/socket.h>


#define SIZE_OF_BUF 32
#define CLIENT_PORT 7777
#define SERVER_PORT 8888
#define CLEINT_ADDRES "10.213.204.201"

char *server_ip;