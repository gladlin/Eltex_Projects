#include "shop.h"

extern int left_buyers;

void *start_provider(void *products_list) {
  struct product *products = (struct product *)products_list;

  int add = 500;
  while (left_buyers) {
    for (int i = 0; i < PRODUCTS; i++) {
      if (products[i].amount == 0) {
        if (pthread_mutex_trylock(&products[i].the_mutex) == 0) {
          products[i].amount += add;
          pthread_mutex_unlock(&products[i].the_mutex);

          printf("Погрузчик добавил в магазин %d товаров %d, теперь там %d\n",
                 i + 1, add, products[i].amount);
          sleep(2);
          break;
        }
      }
    }
  }
  printf("\nНужды всех покупателей были удовлетворены!");

  return NULL;
}