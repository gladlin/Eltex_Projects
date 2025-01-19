#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define LEN_OF_ARG 10

struct abonent {
  struct abonent *prev;
  char name[LEN_OF_ARG];
  char second_name[LEN_OF_ARG];
  char tel[LEN_OF_ARG];
  struct abonent *next;
};

extern struct abonent *tail;
extern struct abonent *head;

void search_for_user();
void add_abonent();
void delete_user();
void print_all_users();
char *write_to_string();
void free_all();