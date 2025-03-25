#include <stdio.h>
#include <pthread.h>

#define N 128

int launch_threads();
void *print_thread(void *index);