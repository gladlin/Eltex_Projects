#include "shop.h"

void *start_provider(void *products_list)
{
    struct product *products = (struct product*)products_list;
    int add = 500;
    while(1)
    {
        for(int i = 0; i < PRODUCTS; i++)
        {
            if(buyer->products[i].amount == 0)
            {
                if (pthread_mutex_trylock(&buyer->products[i].the_mutex) == 0)
                {
                    buyer->products[i].amount += add;
                    pthread_mutex_unlock(&buyer->products[i].the_mutex);

                    printf("Погрузчик %d добавил в магазин %d товаров %d, теперь там %d\n", buyer.thread_index, i+1, add, buyer->products[i].amount);
                    sleep(1);
                    break;
                }
            }
        }
    }//фикл получается бесконечный, надо проверять как покупатели не спят

    return NULL;
}