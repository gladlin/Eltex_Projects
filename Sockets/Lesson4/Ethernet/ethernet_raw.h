#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <net/if.h>  
#include <sys/socket.h>


#define SIZE_OF_BUF 32
#define CLIENT_PORT 7777
#define SERVER_PORT 8888
#define CLIENT_ADDRESS "172.23.29.46"
#define SERVER_ADDRESS "127.0.0.1"
#define CLIENT_MAC "\x08\x00\x27\xaa\x1b\xcb"
#define SERVER_MAC "\x08\x00\x27\xa4\xb3\x8c"