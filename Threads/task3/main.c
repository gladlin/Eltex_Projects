#include "shop.h"

struct product products_list[PRODUCTS];

int main()
{
    for(int i = 0; i < PRODUCTS; i++)
    {
        products_list[i].amount = 5000;
        pthread_mutex_init(&products_list[i].the_mutex, NULL);
    }

    create_shop(products_list);

    for(int i = 0; i < PRODUCTS; i++)
    {
        pthread_mutex_destroy(&products_list[i].the_mutex);
    }
}