#include "increment.h"

extern int a;

void *increment_number()
{
    while (1) {
        if (a >= PTHREAD_AMOUNT * MULTIPLIER)
            break;
        a += 1;
    }
    return NULL;
}