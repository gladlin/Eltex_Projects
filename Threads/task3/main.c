#include "shop.h"

struct product products_list[PRODUCTS];

int main()
{
    for(int i = 0; i < PRODUCTS; i++)
    {
        products_list[i].amount = 10000;
        products_list[i].the_mutex = PTHREAD_MUTEX_INITIALIZER;
    }

    create_shop(products_list);
}