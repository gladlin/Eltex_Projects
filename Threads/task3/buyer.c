#include "shop.h"

void *create_buyer(void *info_thread)
{
    struct thread_and_shops *buyer = (struct thread_and_shops*)info_thread;
    int need = 100000;
    while(need > 0)
    {
        for(int i = 0; i < PRODUCTS; i++)
        {
            if (pthread_mutex_trylock(&buyer->product_list[i].the_mutex) == 0)
            {
                int result = (buyer->product_list[i].amount < need) ? buyer->product_list[i].amount : need;
                need -= result;
                buyer->product_list[i].amount -= result;

                printf("Покупатель %d купил в %d магазине %d товаров\n", buyer.thread_index, i+1, result);
                pthread_mutex_unlock(&buyer->product_list[i].the_mutex);
                sleep(2);
                break;
            }
        }
    }

    return NULL;
}