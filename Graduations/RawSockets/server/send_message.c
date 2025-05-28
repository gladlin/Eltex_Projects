#include "server.h"

void send_message(struct echo_messages *client, char message[BUFSIZE], int fd) 
{
    if (strncmp(message, "exit", 4) == 0) 
    {
        delete_user(client);
        return;
    }

    client->messages++;

    char new_message[BUFSIZE];
    memset(new_message, 0, sizeof(new_message));
    snprintf(new_message, sizeof(new_message), "%s %d", message, client->messages);

    new_message[strcspn(new_message, "\n")] = '\0';
    ssize_t sizeofMessage = strlen(new_message);


    char payload_udp[sizeofMessage + 8];
    memset(payload_udp, 0, sizeof(payload_udp));

    struct udphdr *udp_header = (struct udphdr *)payload_udp;
    udp_header->source = htons(PORT);
    udp_header->dest = htons(client->client_addr.sin_port);
    udp_header->len = htons(sizeofMessage + 8);
    udp_header->check = 0;

    socklen_t sizeOfClient = sizeof(client->client_addr);

    if(memcpy(payload_udp + sizeof(struct udphdr), new_message, sizeofMessage) == NULL)
    {
        perror("memcpy");
        return;
    }

    if (sendto(fd, payload_udp, sizeofMessage + 8, 0, (struct sockaddr *)&client->client_addr, sizeOfClient) == -1)
        perror("sendto");

    printf("Сервер отправил сообщение клиенту \n");
}