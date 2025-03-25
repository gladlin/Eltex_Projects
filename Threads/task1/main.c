#include "print_thread.h"

int main()
{
    printf("Вывод и запуск %d потоков:\n", N);
    int result = launch_threads();
    if(result == -1)
        printf("Ошибки при выводе индексов");
    return 0;
}
