#include "workWithFile.h"

int main()
{
    char text[] = "String from file";
    char path[] = "output.txt";

    int len = sizeof(text);
    int result = write_to_file(path, text, len);
    if(result != 1)
        return -1;

    result = read_from_file(path, len);
    if(result != 1)
        return -1;
    printf("\nДанные успешно записаны в файл!\n");
    return 0;
}