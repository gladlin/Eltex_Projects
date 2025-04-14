#include "systemV.h"

int main()
{
    char *message = "Hello";
    const int message_size = 16;

    key_t key = ftok(SHM_NAME, PROJ_ID);
    if(key == -1)
    {
        perror("ftok server");
        exit(1);
    }

    int shmid = shmget(key, message_size, IPC_CREAT | 0666);
    if(shmid == -1)
    {
        perror("shmget server");
        exit(1);
    }

    char *data = shmat(shmid, NULL, 0);
    if (data == (void *)-1)
    {
        perror("shmat server");
        exit(1);
    }

    strncpy(data, message, message_size);
    printf("Сервер отправил сообщение: %s\n", message);
    
    while(strcmp(data, message) == 0)
        usleep(100000);

    printf("Сервер получил сообщение: %s\n", data);

    if (shmdt(data) == -1)
    {
        perror("shmdt server");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl server");
        exit(1);
    }

    return 0;
}