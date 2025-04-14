#include "client.h"

int flag_is_connected = 1;
struct message *shm_base_message;

int main()
{
    connectToChat();
    return 0;
}

int connectToChat()
{
    int shm_user_fd;
    if ((shm_user_fd = shm_open(SHM_USER, O_RDWR, 0666)) == -1)
    {
        perror("shm_user_open client");
        exit(1);
    }

    char *shm_base_username = mmap(NULL, MAX_USERNAME, PROT_READ | PROT_WRITE, MAP_SHARED, shm_user_fd, 0);
    if (shm_base_username == MAP_FAILED)
    {
        perror("mmap shm_base_username client");
        close(shm_user_fd);
        exit(1);
    }

    printf("Введите свое имя, чтобы присоединиться к чату: ");
    char username[MAX_USERNAME];

    if (fgets(username, MAX_USERNAME, stdin) == NULL)
    {
        printf("Ошибка ввода имени\n");
        munmap(shm_base_username, MAX_USERNAME);
        close(shm_user_fd);
        exit(1);
    }
    username[strcspn(username, "\n")] = '\0';

    if (strlen(username) >= MAX_USERNAME)
    {
        printf("Имя должно быть короче %d символов\n", MAX_USERNAME);
        munmap(shm_base_username, MAX_USERNAME);
        close(shm_user_fd);
        exit(1);
    }

    strcpy(shm_base_username, username);
    usleep(500000);

    start_thread_client(username);

    memset(shm_base_username, 0, MAX_USERNAME);
    munmap(shm_base_username, MAX_USERNAME);
    close(shm_user_fd);
    return 0;
}