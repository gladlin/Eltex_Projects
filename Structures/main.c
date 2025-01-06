#include "handbook.h"

struct abonent list_of_abonents[N];
struct abonent empty_abonent;

int main() {
  int answer = 0;
  char c;
  while (answer != 5) {
    printf("\nМеню:\n1) Добавить абонента\n2) Удалить абонента\n3) Поиск "
           "абонентов по имени\n4) Вывод всех записей\n5) Выход");
    printf("\nВведите выбранный пункт меню : ");
    if (scanf("%d%c", &answer, &c) != 2 || c != '\n') {
      printf("\nВводите только корректный номер пункта меню!");
      return -1;
    }
    if (answer > 5 || answer < 1) {
      printf("\nВводите только существующий номер пункта меню!");
      return -1;
    }
    switch (answer) {
    case 1:
      add_abonent();
      break;
    case 2:
      delete_user();
      break;
    case 3:
      search_for_user();
      break;
    case 4:
      print_all_users();
      break;
    case 5:
      return 0;
    }
  }
  return 0;
}
