#include "handbook.h"

static int written = 0;

void add_abonent() {
  if (written >= N) {
    printf("Все места для создания абонентов уже заняты, удалите какой-либо "
           "абонент и добавьте новый еще раз\n");
    return;
  }

  printf("\nВведите имя пользователя: \n");
  char *result_name = write_to_string();
  if (result_name == NULL) {
    free(result_name);
    return;
  }

  printf("Введите фамилию пользователя: \n");
  char *result_sname = write_to_string();
  if (result_sname == NULL) {
    free(result_name);
    free(result_sname);
    return;
  }

  printf("Введите номер телефона пользователя: \n");
  char *result_tel = write_to_string();
  if (result_tel == NULL) {
    free(result_name);
    free(result_sname);
    free(result_tel);
    return;
  }

  int index = get_first_empty();
  strcpy(list_of_abonents[index].name, result_name);
  strcpy(list_of_abonents[index].second_name, result_sname);
  strcpy(list_of_abonents[index].tel, result_tel);
  printf("Новый пользователь успешно добавлен!\n");
  written++;
  free(result_name);
  free(result_sname);
  free(result_tel);
}