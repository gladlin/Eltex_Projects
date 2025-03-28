#include "mc.h"

void init_ncurses() {
    initscr();
    noecho();
    curs_set(0); 
    keypad(stdscr, TRUE);
}