#include "handbook.h"

void search_for_user() {
  printf("Введите имя абонента, которого вы хотите найти: ");
  char *name = write_to_string();
  if (name == NULL) {
    free(name);
    return;
  }

  int count_users = 0;
  printf("Список всех абонентов с именем %s:\n", name);
  for (int i = 0; i < N; i++) {
    if (strcmp(list_of_abonents[i].name, name) == 0) {
      count_users++;
      printf("%d) Имя: %s, Фамилия: %s, Номер телефона: %s\n", count_users,
             list_of_abonents[i].name, list_of_abonents[i].second_name,
             list_of_abonents[i].tel);
    }
  }
  if (count_users == 0)
    printf("Абонент с именем %s не существует\n", name);
  free(name);
}