#include "ethernet_raw.h"

unsigned short checksum(unsigned short *buf, int nwords)
{
    unsigned long sum = 0;
    for (; nwords > 0; nwords--)
        sum += *buf++;

    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);

    return (unsigned short)(~sum);
}


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

    int client_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (client_fd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    char packet[14 + 20 + 8 + len_payload];
    memset(packet, 0, sizeof(packet));

    struct ethhdr* ethernet_header = (struct ethhdr *)packet;
    unsigned char client_mac[6] = {0x08, 0x00, 0x27, 0xaa, 0xbb, 0xcc}; // надо заменить
    unsigned char server_mac[6] = {0x08, 0x00, 0x27, 0xdd, 0xee, 0xff}; // надо заменить

    memcpy(ethernet_header->h_source, client_mac, ETH_ALEN);
    memcpy(ethernet_header->h_dest, server_mac, ETH_ALEN);  
    

    ethernet_header->h_proto = htons(ETH_P_IP);

    struct iphdr *ip_header = (struct iphdr*)(packet + sizeof(struct ethhdr));
    ip_header->version = 4;
    ip_header->ihl = 5;
    ip_header->tos = 0;
    ip_header->tot_len = htons(sizeof(packet));
    ip_header->id = htons(56789);
    ip_header->frag_off = 0;
    ip_header->ttl = 64;
    ip_header->protocol = 17;
    ip_header->check = checksum((unsigned short *)ip_header, sizeof(struct iphdr)/2);
    ip_header->saddr = inet_addr(CLIENT_ADDRESS);
    ip_header->daddr = inet_addr(SERVER_ADDRESS);

    struct udphdr *udp_header = (struct udphdr *)(packet + ip_header->ihl*4 + sizeof(struct ethhdr));
    udp_header->source = CLIENT_PORT;
    udp_header->dest = SERVER_PORT;
    udp_header->len = htons(len_payload + 8);
    udp_header->check = 0;

    if(memcpy(packet + sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr), payload, len_payload))
    {
        perror("memcpy");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    char *ifname = "etho1"; // надо поменять в соответствии с тем что находится на виртуалках
    int index = if_nametoindex(ifname);
    if(index == -1)
    {
        perror("if_nametoindex");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_ll server;
    server.sll_family = AF_PACKET;
    memcpy(server.sll_addr, SERVER_MAC, ETH_ALEN);
    server.sll_ifindex = index;
    server.sll_halen = ETH_ALEN;
    
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