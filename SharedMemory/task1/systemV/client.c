#include "systemV.h"

int main()
{
    char *message = "Hi";
    const int message_size = 16;

    key_t key = ftok(SHM_NAME, PROJ_ID);
    if(key == -1)
    {
        perror("ftok client");
        exit(1);
    }

    int shmid = shmget(key, message_size, IPC_CREAT | 0666);
    if(shmid == -1)
    {
        perror("shmget client");
        exit(1);
    }

    char *data = shmat(shmid, NULL, 0);
    if (data == (void *)-1)
    {
        perror("shmat client");
        exit(1);
    }

    printf("Клиент получил сообщение: %s\n", data);

    strncpy(data, message, message_size);
    printf("Клиент отправил сообщение: %s\n", message);

    if (shmdt(data) == -1)
    {
        perror("shmdt client");
        exit(1);
    }

    return 0;
}