#include "ip_raw.h"

int main()
{
    struct sockaddr_in server, client;
    int server_fd;

    if((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = SERVER_PORT;
    server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    if(bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("bind");
        close(server_fd);
        exit(1);
    }
    
    char buf[SIZE_OF_BUF];
    socklen_t sizeof_client = sizeof(client);
    if(recvfrom(server_fd, buf, SIZE_OF_BUF, 0, (struct sockaddr *)&client, &sizeof_client) == -1)
    {
        perror("recvfrom");
        close(server_fd);
        exit(1);
    }

    printf("Сервер принял строку: %s\n", buf);
    buf[0] += 1;
    printf("Сервер изменил строку на: %s\n", buf);

    if(sendto(server_fd, buf, SIZE_OF_BUF, 0, (struct sockaddr *)&client, sizeof_client) == -1)
    {
        perror("sendto");
        close(server_fd);
        exit(1);
    }
    printf("Сервер отправил строку клиенту\n");

    close(server_fd);
}