#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define BUYERS 3
#define PROVIDERS 1
#define PRODUCTS 5

struct product {
  unsigned int amount;
  pthread_mutex_t the_mutex;
};

struct thread_and_shops {
  int thread_index;
  struct product *product_list;
};

void *start_provider(void *products_list);
void *create_buyer(void *info_thread);
int create_shop(struct product products_list[PRODUCTS]);