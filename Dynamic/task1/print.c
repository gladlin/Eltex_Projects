#include "handbook.h"

void print_all_users() {
  int counter = 1;
  printf("\nВывод всех зарегистрированных абонентов\n");
  struct abonent *current_Abonent = head;
  while (current_Abonent != NULL) {
    printf("%d) Имя: %s, Фамилия: %s, Номер телефона: %s\n", counter,
           current_Abonent->name, current_Abonent->second_name,
           current_Abonent->tel);
    counter++;
    current_Abonent = current_Abonent->next;
  }
}