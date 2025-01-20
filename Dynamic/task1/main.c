#include "handbook.h"

struct abonent *tail = NULL;
struct abonent *head = NULL;

int main() {
  int answer = 0;
  char c;
  while (answer != 5) {
    printf("\nМеню:\n1) Добавить абонента\n2) Удалить абонента\n3) Поиск "
           "абонентов по имени\n4) Вывод всех записей\n5) Выход");
    printf("\nВведите выбранный пункт меню : ");

    if (scanf("%d%c", &answer, &c) != 2 || c != '\n' ||
        (answer > 5 || answer < 1)) {
      printf("\nВводите только корректный номер пункта меню!");
      while (getchar() != '\n')
        ;
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
      free_all();
      return 0;
    }
  }
  free_all();
  return 0;
}
