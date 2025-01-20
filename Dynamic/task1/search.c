#include "handbook.h"

void search_for_user() {
  printf("Введите имя абонента, которого вы хотите найти: ");
  char *name = write_to_string();
  if (name == NULL) {
    free(name);
    return;
  }
  int count_users = 0;
  struct abonent *current_Abonent = head;
  while (current_Abonent != NULL) {
    if (strcmp(current_Abonent->name, name) == 0) {
      count_users++;
      printf("%d) Имя: %s, Фамилия: %s, Номер телефона: %s\n", count_users,
             current_Abonent->name, current_Abonent->second_name,
             current_Abonent->tel);
    }
    current_Abonent = current_Abonent->next;
  }

  if (count_users == 0)
    printf("Абонент с именем %s не существует\n", name);
  free(name);
}