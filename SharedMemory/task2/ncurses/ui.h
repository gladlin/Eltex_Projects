#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>


#define UI_INPUT_HEIGHT 3

void init_ui(void);

void cleanup_ui(void);

void add_message(const char *username, const char *msg);

void update_user_list(char users[][32], int user_count);

void get_input(char *buffer, int max_len);

#endif
