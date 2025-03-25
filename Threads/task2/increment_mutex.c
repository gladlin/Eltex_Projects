#include "increment.h"

extern int a;
static pthread_mutex_t the_mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment_number_mutex()
{
    while (1) {
        pthread_mutex_lock(&the_mutex);
        if(a < PTHREAD_AMOUNT * MULTIPLIER)
            a+=1;
        else{
            pthread_mutex_unlock(&the_mutex);
            break;
        }
        pthread_mutex_unlock(&the_mutex);
    }
    return NULL;
}