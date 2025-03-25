#include "manyProcess.h"

int main()
{
    if (!createManyProcess())
    {
        perror("\nОшибки при выполнении кода\n");
        return -1;
    }
    printf("\nВсе прошло успешно!\n");
    return 0;
}
