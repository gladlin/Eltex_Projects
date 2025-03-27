#include "client_server.h"

int main()
{
    char *namePipe = "pipe";
    mkfifo(namePipe, 0666);

    int fd = open(namePipe, O_WRONLY);
    char buff[4] = "Hi!";
    if(write(fd, buff, sizeof(buff)) != sizeof(buff))
        perror("Ошибка при записи данных в канал");
    printf("Отправленное сообщение %s\n", buff);
    close(fd);
    return 0;
}