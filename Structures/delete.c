#include "handbook.h"

void delete_user() {
  printf("Введите номер телефона абонента, который вы хотите удалить: ");
  char *tel = write_to_string();
  if (tel == NULL) {
    free(tel);
    return;
  }

  for (int i = 0; i < N; i++) {
    if (strcmp(list_of_abonents[i].tel, tel) == 0) {
      list_of_abonents[i] = empty_abonent;
      printf("\nАбонент с номером телефона %s удален\n", tel);
      free(tel);
      return;
    }
  }
  printf("Абонент с номером телефона %s не существует\n", tel);
  free(tel);
}