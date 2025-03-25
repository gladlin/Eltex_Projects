#include <stdio.h>
#include <pthread.h>

#define BUYERS 3
#define PROVIDERS 1
#define PRODUCTS 5

struct product
{
    unsigned int amount;
    pthread_mutex_t the_mutex;
}

struct thread_and_shops
{
    int thread_index;
    struct product* product_list;
}