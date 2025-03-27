#include "unnamePipe.h"

int create_Pipe()
{
    int fd[2];
    pipe(fd);
    if(fork())
    {
        close(fd[0]);
        char buff[4] = "Hi!";
        int res = write(fd[1], buff, sizeof(buff));
        printf("Отправил сообщение на другую сторону: %s\n", buff);
        
        if(res != sizeof(buff))
            perror("Не все символы записались в канал");
        close(fd[1]);
    }
    else
    {
        close(fd[1]);

        char message[4];
        if(read(fd[0], message, sizeof(message)) != sizeof(message))
            perror("Не все символы считались\n");
            
        printf("Сообщение от другой стороны: %s\n", message);
        close(fd[0]);
    }
    return 0;
}