#include "udp_raw.h"

int main()
{
    char payload[SIZE_OF_BUF];
    if(fgets(payload, SIZE_OF_BUF, stdin) == NULL)
    {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    payload[strcspn(payload, "\n")] = '\0';
    ssize_t payload_len = strlen(payload);

    
    int client_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(client_fd == -1)
    {
        perror("socket");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    char packet_udp[payload_len + 8];
    if(memset(packet_udp, 0, sizeof(packet_udp)) == NULL)
    {
        perror("memset");
        close(client_fd);
        exit(EXIT_FAILURE);
    }


    struct udphdr *udp_header = (struct udphdr *)packet_udp;
    udp_header->source = CLIENT_PORT;
    udp_header->dest = SERVER_PORT;
    udp_header->len = htons(payload_len + 8);
    udp_header->check = 0;

    if(memcpy(packet_udp + sizeof(struct udphdr), payload, payload_len) == NULL)
    {
        perror("memcpy");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);


    char zero[8] = {0};
    if(memcpy(server.sin_zero, zero, 8) == NULL)
    {
        perror("memcpy");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    socklen_t server_len = sizeof(server);

    if(sendto(client_fd, packet_udp, sizeof(packet_udp), 0, (struct sockaddr *)&server, server_len) == -1)
    {
        perror("socket");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    printf("Клиент отправил строку серверу: %s\n", payload);

    char answer[20 + 8 + SIZE_OF_BUF];
    while(1)
    {
        if(recvfrom(client_fd, answer, sizeof(answer), 0, (struct sockaddr *)&server, &server_len) == -1)
        {
            perror("socket");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
        struct iphdr *ip_header = (struct iphdr *)answer;
        int ipheader_len = ip_header->ihl * 4;
        struct udphdr *udp_header = (struct udphdr *)(answer + ipheader_len);
        if(udp_header->dest == CLIENT_PORT && udp_header->source == SERVER_PORT)
        {
            char *payload = (char *)(answer + ipheader_len +  sizeof(struct udphdr));
            printf("Клиент получил сообщение от сервера: %s\n", payload);
            break;
        }
    }
    
    close(client_fd);

    return 0;
}