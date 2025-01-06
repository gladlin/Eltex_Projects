#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define LEN_OF_ARG 10

struct abonent {
  char name[LEN_OF_ARG];
  char second_name[LEN_OF_ARG];
  char tel[LEN_OF_ARG];
};

extern struct abonent list_of_abonents[N];
extern struct abonent empty_abonent;

void search_for_user();
void add_abonent();
void delete_user();
void print_all_users();
char *write_to_string();
int get_first_empty();