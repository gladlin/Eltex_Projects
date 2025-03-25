#include <stdio.h>
#include <pthread.h>

#define PTHREAD_AMOUNT 4
#define MULTIPLIER 10000000

void *increment_number();
void *increment_number_mutex();
int start_threads(int mode);