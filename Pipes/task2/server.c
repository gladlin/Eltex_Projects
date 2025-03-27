#include "client_server.h"

int main()
{
    char *namePipe = "pipe";
    mkfifo(namePipe, 0666);

    int fd = open(namePipe, O_RDONLY);
    char buff[4];
    if(read(fd, buff, sizeof(buff)) != sizeof(buff))
        perror("Ошибка при чтении данных из канала");
    printf("Полученное сообщение %s\n", buff); 
    close(fd);
    return 0;
}