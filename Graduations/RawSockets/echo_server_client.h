
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#define IP_ADDRESS "127.0.0.1"
#define PORT 23456
#define BUFSIZE 128

struct echo_messages {
    struct sockaddr_in client_addr;
    int messages;
    struct echo_messages *next_client;
};