#include "handbook.h"

static int written = 0;

void add_abonent() {
  char *result_name = NULL;
  char *result_sname = NULL;
  char *result_tel = NULL;

  printf("\nВведите имя пользователя: \n");
  result_name = write_to_string();
  if (result_name == NULL) goto cleanup;

  printf("Введите фамилию пользователя: \n");
  result_sname = write_to_string();
  if (result_sname == NULL) goto cleanup;

  printf("Введите номер телефона пользователя: \n");
  result_tel = write_to_string();
  if (result_tel == NULL) goto cleanup;

  struct abonent *new_abonent =
      (struct abonent *)malloc(sizeof(struct abonent)); //почему то утечка памяти при удалении пользователя
  if (new_abonent == NULL) {
    printf("Ошибка выделения памяти!\n");
    return;
  }

  strncpy(new_abonent->name, result_name, LEN_OF_ARG);
  strncpy(new_abonent->second_name, result_sname, LEN_OF_ARG);
  strncpy(new_abonent->tel, result_tel, LEN_OF_ARG);

  new_abonent->prev = tail;
  new_abonent->next = NULL;
  if (head == NULL)
    head = new_abonent;  //если создается первый элемент
  else
    tail->next = new_abonent;

  tail = new_abonent;
  printf("Новый пользователь успешно добавлен!\n");
  written++;
  goto cleanup;

cleanup:
  free(result_name);
  free(result_sname);
  free(result_tel);
}