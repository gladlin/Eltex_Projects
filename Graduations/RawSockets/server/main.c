#include "../echo_server_client.h"

struct echo_messages *head = NULL;

struct echo_messages *create_user(struct sockaddr_in *client) 
{
    struct echo_messages *current = head;
    while (current != NULL) 
    {
        if (current->client_addr.sin_addr.s_addr == client->sin_addr.s_addr &&
            current->client_addr.sin_port == client->sin_port) 
            return current;

        current = current->next_client;
    }

    struct echo_messages *new_client = malloc(sizeof(struct echo_messages));
    if (new_client == NULL) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_client->client_addr = *client;
    new_client->messages = 0;
    new_client->next_client = head;
    head = new_client;
    return new_client;
}

void delete_user(struct echo_messages *client) 
{
    if (client == head) 
    {
        head = head->next_client;
        free(client);
        return;
    }

    struct echo_messages *prev = head;
    while (prev->next_client && prev->next_client != client) 
    {
        prev = prev->next_client;
    }

    if (prev->next_client == client) 
    {
        prev->next_client = client->next_client;
        free(client);
    }
}

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

void clear_all() 
{
    struct echo_messages *current = head;
    while (current != NULL) 
    {
        struct echo_messages *next = current->next_client;
        free(current);
        current = next;
    }
    head = NULL;
}

int main() 
{
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (fd < 0) 
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in *client = malloc(sizeof(struct sockaddr_in));
    char buf[BUFSIZE];

    while (1)
    {
        int res = recvfrom(fd, buf, BUFSIZE, 0, NULL, NULL);
        if (res == -1) 
        {
            perror("recvfrom");
            clear_all();
            break;
        }

        struct iphdr *ip_header = (struct iphdr *)buf;
        struct udphdr *udp_header = (struct udphdr *)(buf + ip_header->ihl * 4);

        char *ip_address_package = inet_ntoa(*(struct in_addr *)&ip_header->daddr);
        if (strcmp(ip_address_package, IP_ADDRESS) != 0)
            continue;

        int port_package = ntohs(udp_header->dest);
        if (port_package != PORT)
            continue;

        // мб стоит сверить что сообщение предназначалось именно нам, а не кому то другому, а то raw сокет будет получать все udp сообщения

        printf("Клиент прошел все проверки\n");

        char *payload = (char *)(buf + ip_header->ihl * 4 + sizeof(struct udphdr));

        int offset = ip_header->ihl * 4 + sizeof(struct udphdr);

        if (res <= offset) 
            continue;

        int payload_len = res - offset;
        payload[payload_len] = '\0';

        client->sin_family = AF_INET;
        client->sin_addr.s_addr = ip_header->saddr;
        client->sin_port = ntohs(udp_header->source);
        printf("\nport %d %d \n", client->sin_port, client->sin_addr.s_addr);

        struct echo_messages *current_user = create_user(client);
        send_message(current_user, payload, fd);
    }
    close(fd);
    free(client);

    clear_all();
    return 0;
}
