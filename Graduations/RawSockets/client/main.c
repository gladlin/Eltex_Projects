#include "../echo_server_client.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Введите свой порт в качестве аргумента для запуска программы!\n");
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    if(port <= 0)
    { 
        printf("Введите корректное значение порта!\n");
        exit(EXIT_FAILURE);
    }
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd == -1)
    {
        perror("socket client");
        exit(EXIT_FAILURE);
    }

    srandom(time(NULL));
    struct sockaddr_in client_addr = {0};
    client_addr.sin_family = AF_INET;

    client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    
    bind(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr));

    struct sockaddr_in send_to;
    send_to.sin_port = htons(PORT);
    send_to.sin_family = AF_INET;
    inet_pton(AF_INET, IP_ADDRESS, &send_to.sin_addr);

    socklen_t sizeofServer = sizeof(send_to);

    char message[BUFSIZE] = "";
    
    while(strcmp(message, "exit") != 0)
    {
        printf("\nВведите сообщение: ");
        if(fgets(message, BUFSIZE, stdin) == NULL)
        {
            perror("fgets client");
            close(client_fd);
            exit(EXIT_FAILURE);
        }

        message[strcspn(message, "\n")] = '\0';

        if(sendto(client_fd, message, strlen(message), 0, (struct sockaddr *)&send_to, sizeofServer) == -1)
        {
            perror("sendto client");
            close(client_fd);
            exit(EXIT_FAILURE);
        }

        if(strcmp(message, "exit") == 0)
            break;

        memset(message, 0, sizeof(message));
        if(recvfrom(client_fd, message, BUFSIZE, 0, (struct sockaddr *)&send_to, &sizeofServer) == -1)
        {
            perror("recvfrom client");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
        printf("Сообщение от сервера: %s", message);
    }

    close(client_fd);
    return 0;
}