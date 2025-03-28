#include "mc.h"


int main() {
    Panel left, right;
    getcwd(left.path, sizeof(left.path));
    strcpy(right.path, left.path);
    list_dir(&left);
    list_dir(&right);

    init_ncurses();
    run_program(&left, &right);

    for (int i = 0; i < left.count; i++) free(left.files[i]);
    for (int i = 0; i < right.count; i++) free(right.files[i]);

    endwin();
    return 0;
}