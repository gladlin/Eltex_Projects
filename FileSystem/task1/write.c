#include "workWithFile.h"

int write_to_file(char *path, char* text, int len)
{
    int fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if(fd == -1)
    {
        perror("Ошибка при создании или открытии файла");
        close(fd);
        exit(-1);
    }
    ssize_t write_symb = write(fd, text, len);
    if (write_symb < len)
    {
        close(fd);
        perror("Ошибка при записи данных в файл");
        exit(-1);
    }
    close(fd);
    return 1;
}