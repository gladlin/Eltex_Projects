#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_FILES 1024

typedef struct {
    char *files[MAX_FILES];
    int count;
    int current;
    char path[1024];
} Panel;

void run_program(Panel *left, Panel *right);
int handle_input(int ch, Panel *active);
void list_dir(Panel *panel);
void change_dir(Panel *panel);
void draw_panel(Panel *panel, int x, int active);
void init_ncurses();