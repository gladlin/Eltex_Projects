#include "twoProcess.h"

int main()
{
    int res = createSecondProcess();
    if(res != 0)
    {
        printf("\nОшибки при выполнении кода");
        return -1;
    }
    return 0;
}