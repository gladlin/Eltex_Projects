#include "udp_raw.h"

int main()
{
    char buf[SIZE_OF_BUF];
    if(fgets(buf, SIZE_OF_BUF, stdin) == NULL)
    {
        perror("fgets");
        return -1;
    }
    int client_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    struct sockaddr_in client;
    
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = inet_addr(CLEINT_ADDRES);

    if(bind(client_fd, (struct sockaddr *)&client, sizeof(struct sockaddr)) == -1)
    {
        perror("bind"); // cannot assign requested address
        close(client_fd);
        return -1;
    }

    if(setsockopt(client_fd, IPPROTO_IP, IP_HDRINCL, NULL, sizeof(int)) < 0 )
    {
        perror("setsockopt");
        close(client_fd);
        return -1;
    }

    printf("I am here\n");
    struct udphdr *buf_header = (struct udphdr *)(SIZE_OF_BUF + sizeof(struct iphdr));
    buf_header->source = htons(CLIENT_PORT);
    buf_header->dest = htonl(SERVER_PORT);
    buf_header->len = sizeof(buf) + sizeof(struct iphdr);
    buf_header->check = 0;
    

    char newBuf[SIZE_OF_BUF + 8];

    if(strcpy(newBuf, (char *)buf_header) ==  NULL)
    {
        perror("strcpy");
        close(client_fd);
        return -1;
    }

    if(strcat(newBuf, buf) ==  NULL)
    {
        perror("strcpy");
        close(client_fd);
        return -1;
    }

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(server_ip);

    if(sendto(client_fd, newBuf, sizeof(newBuf) , 0, (struct sockaddr *)&server, (socklen_t)sizeof(struct sockaddr)) == -1)
    {
        perror("sendto");
        close(client_fd);
        return -1;
    }
    printf("Клиент отправил серверу строку: %s\n", buf);

    struct udphdr newMessage[SIZE_OF_BUF + 8];

    while(1)
    {
        if(recvfrom(client_fd, newBuf,  sizeof(newBuf) , 0, (struct sockaddr *)&server,  (socklen_t *)sizeof(struct sockaddr)) != -1)
        {
            memcpy(newMessage, newBuf, 8);
            if(newMessage->dest == buf_header->source)
            {
                printf("Клиент получил сообщение %s\n", newBuf);
                break;
            }
        }
        else
        {
            perror("recvfrom");
            close(client_fd);
            return -1;
        }
    }


    return 0;
}