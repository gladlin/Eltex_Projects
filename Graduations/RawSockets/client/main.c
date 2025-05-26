#include "../echo_server_client.h"

void change_Symb(char *message)
{
    while(*message != '\0')
    {
        if(*message == '\n')
        {
            *message = '\0';
            return;
        }
        message++;
    }
}

int main()
{
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd == -1)
    {
        perror("socket client");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client_addr = {0};
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(12345); // генерировать значение и умножить его на 10к
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bind(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    printf("Мой адрес и порт: %d %d\n", client_addr.sin_addr.s_addr, client_addr.sin_port);

    struct sockaddr_in send_to;
    send_to.sin_port = htons(PORT);
    send_to.sin_family = AF_INET;
    inet_pton(AF_INET, IP_ADDRESS, &send_to.sin_addr);

    socklen_t sizeofServer = sizeof(send_to);

    char message[BUFSIZE] = "";
    
    printf("\nВведите сообщение: ");
    if(fgets(message, BUFSIZE, stdin) == NULL)
    {
        perror("fgets client");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    change_Symb(message);

    while(strcmp(message, "exit") != 0)
    {
        if(sendto(client_fd, message, BUFSIZE, 0, (struct sockaddr *)&send_to, sizeofServer) == -1)
        {
            perror("sendto client");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
        printf("Отправил сообщение\n");
        if(recvfrom(client_fd, message, BUFSIZE, 0, (struct sockaddr *)&send_to, &sizeofServer) == -1)
        {
            perror("recvfrom client");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
        printf("Сообщение от сервера: %s", message);

        printf("\nВведите сообщение: ");
        if(fgets(message, BUFSIZE, stdin) == NULL)
        {
            perror("fgets client");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
        change_Symb(message);
    }
    close(client_fd);
    return 0;
}