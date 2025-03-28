#include "print_thread.h"

int launch_threads()
{
    int indexes[N];
    pthread_t new_threads[N];
    for(int i = 0; i < N; i++)
    {
        indexes[i] = i;
        int result = pthread_create(&new_threads[i], NULL, print_thread, (void *)&indexes[i]);

        if(result != 0)
        {
            perror("Ошибка создания потока");
            return -1;
        }
    }
    for(int j = 0; j < N; j++)
        pthread_join(new_threads[j], NULL);

    return 0;
}

void *print_thread(void *index)
{
    int *new_index = (int*)index;
    printf("Запущен поток номер %d\n", *new_index+1);

    return NULL;
}