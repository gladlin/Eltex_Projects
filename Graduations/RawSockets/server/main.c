#include "server.h"

struct echo_messages *head = NULL;

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

        char *payload = (char *)(buf + ip_header->ihl * 4 + sizeof(struct udphdr));

        int offset = ip_header->ihl * 4 + sizeof(struct udphdr);

        if (res <= offset) 
            continue;

        int payload_len = res - offset;
        payload[payload_len] = '\0';

        client->sin_family = AF_INET;
        client->sin_addr.s_addr = ip_header->saddr;
        client->sin_port = ntohs(udp_header->source);

        struct echo_messages *current_user = create_user(client);
        send_message(current_user, payload, fd);
    }
    close(fd);
    free(client);

    clear_all();
    return 0;
}
