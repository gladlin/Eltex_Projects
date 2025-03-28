#include "workWithFile.h"

int read_from_file(char *path, int len)
{
    int fd = open(path, O_RDONLY);
    if(fd < 1)
    {
        perror("Ошибка при открытии файла");
        exit(-1);
    }
    char result_string[len];
    memset(result_string, 0, sizeof(result_string));

    for(int i = 0; i < len-1; i++)
    {
        if(lseek(fd, -2 -i, SEEK_END) == (off_t)-1)
        {
            perror("Ошибка при позиционировании");
            close(fd);
            exit(-1);
        }
        if(read(fd, &result_string[i], sizeof(char)) != 1)
        {
            perror("Ошибка при считывании данных");
            close(fd);
            exit(-1);
        }
    }

    printf("Итоговая строка: %s\n", result_string);
    close(fd);
    return 1;
}