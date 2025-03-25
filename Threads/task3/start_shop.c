#include "shop.h"

int create_shop(struct product products_list[PRODUCTS])
{
    if (BUYERS <= 0 || PROVIDERS <= 0 || PRODUCTS <= 0)
    {
        printf("Число покупателей, поставщиков и продуктов не может быть меньше либо равно 0!\n");
        return -1;
    }
    pthread_t buyers_thread[BUYERS];
    struct thread_and_shops info_threads[BUYERS];

    for(int i = 0; i < BUYERS; i++)
    {
        info_threads[i] = {i, products_list} 
        if (pthread_create(&buyers_thread[i], NULL, create_buyer, (void *)&info_thread[i]) != 0)
        {
            perror("Ошибки при создании потока!");
            return -1;
        }
    }

    pthread_t providers_thread;
    if(pthread_create(&providers_thread, NULL, start_provider, (void *)&products_list) != 0)
    {
        perror("Ошибки при создании потока!");
        return -1;
    }
    
    for(int i = 0; i < BUYERS; i++)
    {
        if( pthread_join(&buyers_thread[i], NULL) != 0)
        {
            perror("Ошибка при ожидании потока погрузчика!");
            return -1;
        }
    }

    if (pthread_join(providers_thread, NULL) != 0)
    {
        perror("Ошибка при ожидании потока погрузчика!");
        return -1;
    }
}