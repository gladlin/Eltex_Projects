#include "handbook.h"

void delete_user() {
  printf("Введите номер телефона абонента, который вы хотите удалить: ");
  char *tel = write_to_string();
  if (tel == NULL) {
    free(tel);
    return;
  }

  struct abonent *current_Abonent = head;
  while (current_Abonent != NULL) {
    if (strcmp(current_Abonent->tel, tel) == 0) {
      if (current_Abonent->prev != NULL)
        current_Abonent->prev->next = current_Abonent->next;
      else
        head = current_Abonent->next;

      if (current_Abonent->next != NULL)
        current_Abonent->next->prev = current_Abonent->prev;
      else
        tail = current_Abonent->prev;

      printf("\nАбонент с номером телефона %s удален\n", tel);
      free(current_Abonent);
      free(tel);
      return;
    }
    current_Abonent = current_Abonent->next;
  }

  printf("Абонент с номером телефона %s не существует\n", tel);
  free(tel);
}