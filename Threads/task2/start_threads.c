#include "increment.h"

int a = 0;

int start_threads(int mode)
{
    pthread_t increment_thread[PTHREAD_AMOUNT];
    for(int i = 0; i < PTHREAD_AMOUNT; i++)
    {
        int result;
        if(mode)
            result = pthread_create(&increment_thread[i], NULL, increment_number, NULL);
        else
            result = pthread_create(&increment_thread[i], NULL, increment_number_mutex, NULL);

        if(result != 0)
        {
            perror("Ошибка при создании потока");
            return -1;
        }
    }

    for(int j = 0; j < PTHREAD_AMOUNT; j++)
        pthread_join(increment_thread[j], NULL);
        
    int result = a;
    a = 0;
    return result;
}