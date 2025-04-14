#include "posix.h"

int main()
{
    const char *name = "shared_memory";
    char *message = "Hello";
    const int message_size = 16;
    
    int shm_fd;
    if((shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666)) == -1)
    {
        perror("shm_open server");
        exit(1);
    }
    if(ftruncate(shm_fd, message_size) == -1)
    {
        perror("ftruncate server");
        exit(1);
    }

    char *shm_base = mmap(NULL, message_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_base == MAP_FAILED) {
        perror("mmap server");
        exit(1);
    }

    strncpy(shm_base, message, message_size - 1);
    printf("Сервер отправил сообщение: %s\n", message);

    while(strcmp(shm_base, message) == 0)
        usleep(100000); // проверка на то, записал ли пользователь свое сообщение

    printf("Сервер получил сообщение: %s\n", shm_base);

    if (munmap(shm_base, message_size) == -1)
    {
        perror("munmap server");
        exit(1);
    }

    if (close(shm_fd) == -1) {
        perror("close server");
        exit(1);
    }
    
    if (shm_unlink(name) == -1) {
        perror("shm_unlink server");
        exit(1);
    }
    return 0;
}