#include "increment.h"

int main()
{
    int result = start_threads(0);
    if(result == -1)
        printf("Ошибка при создании потоков");
    printf("Итоговый результат %d без мьютексов\n", result);

    result = start_threads(1);
    if(result == -1)
        printf("Ошибка при создании потоков с мьютексами");
    printf("Итоговый результат %d с мьютеками\n", result);
    return 0;
}