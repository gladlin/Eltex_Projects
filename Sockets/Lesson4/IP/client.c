#include "ip_raw.h"

int main()
{
    char payload[SIZE_OF_BUF];
    if(fgets(payload, SIZE_OF_BUF, stdin) == NULL)
    {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    payload[strcspn(payload, "\n")] = '\0';
    ssize_t len_payload = strlen(payload);

    int client_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (client_fd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int flag = 1;
    if (setsockopt(client_fd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag)) == -1)
    {
        perror("setsockopt");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    char packet[20 + 8 + len_payload];
    if(memset(packet, 0, sizeof(packet)) == NULL)
    {
        perror("memcpy");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    struct iphdr *ip_header = (struct iphdr*)packet;
    ip_header->version = 4;
    ip_header->ihl = 5;
    ip_header->tos = 0;
    ip_header->tot_len = htons(sizeof(packet));
    ip_header->id = htons(56789);
    ip_header->frag_off = 0;
    ip_header->ttl = 64;
    ip_header->protocol = 17;
    ip_header->check = 0;
    ip_header->saddr = inet_addr(CLIENT_ADDRESS);
    ip_header->daddr = inet_addr(SERVER_ADDRESS);

    struct udphdr *udp_header = (struct udphdr *)(packet + ip_header->ihl*4);
    udp_header->source = CLIENT_PORT;
    udp_header->dest = SERVER_PORT;
    udp_header->len = htons(len_payload + 8);
    udp_header->check = 0;

    if(memcpy(packet+sizeof(struct iphdr)+sizeof(struct udphdr), payload, len_payload) == NULL)
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

    if(sendto(client_fd, packet, sizeof(packet), 0, (struct sockaddr *)&server, server_len) == -1)
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
        struct udphdr *newUdphdt = (struct udphdr *)(answer + ip_header->ihl * 4);
        char *newPayload = (char*)(answer + ip_header->ihl * 4 + sizeof(struct udphdr));
        if(newUdphdt->source == SERVER_PORT && newUdphdt->dest == CLIENT_PORT)
        {
            printf("Клиент получил сообщение от сервера: %s\n", newPayload);
            break;
        }
    }
    close(client_fd);

    return 0;
}