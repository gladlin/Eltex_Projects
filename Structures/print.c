#include "handbook.h"

void print_all_users() {
  int counter = 1;
  printf("\nВывод всех зарегистрированных абонентов\n");
  for (int i = 0; i < N; i++) {
    if (list_of_abonents[i].name[0] != '\0') {
      printf("%d) Имя: %s, Фамилия: %s, Номер телефона: %s\n", counter,
             list_of_abonents[i].name, list_of_abonents[i].second_name,
             list_of_abonents[i].tel);
      counter++;
    }
  }
}