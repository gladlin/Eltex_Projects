#include "mc.h"

void draw_panel(Panel *panel, int x, int active) {
    for (int i = 0; i < panel->count; i++) {
        if (i == panel->current)
            attron(A_REVERSE);
        mvprintw(i + 1, x, "%-30s", panel->files[i]);
        if (i == panel->current)
            attroff(A_REVERSE);
    }
    mvprintw(0, x, "%s", panel->path);
    if (active) mvprintw(0, x - 2, "→");
}