#include "posix.h"

int main()
{
    const char *name = "shared_memory";
    const int message_size = 16;
    const char *message = "Hi";
    
    int shm_fd;
    if((shm_fd = shm_open(name, O_RDWR , 0666)) == -1)
    {
        perror("shm_open client");
        exit(1);
    }

    char *shm_base = mmap(NULL, message_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_base == MAP_FAILED) {
        perror("mmap client");
        exit(1);
    }

    printf("Клиент получил сообщение: %s\n", shm_base);

    strncpy(shm_base, message, message_size - 1);

    printf("Клиент отправил сообщение: %s\n", message);
    
    if (munmap(shm_base, message_size) == -1)
    {
        perror("munmap client");
        exit(1);
    }

    if (close(shm_fd) == -1) {
        perror("close client");
        exit(1);
    }
    return 0;
}