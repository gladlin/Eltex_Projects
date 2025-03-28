#include "mc.h"

void run_program(Panel *left, Panel *right) {
    int active_panel = 0;
    Panel *panels[] = { left, right };

    while (1) {
        clear();
        draw_panel(left, 2, active_panel == 0);
        draw_panel(right, 40, active_panel == 1);
        refresh();

        int ch = getch();
        Panel *active = panels[active_panel];

        if (handle_input(ch, active))
            active_panel = 1 - active_panel;
        else if (ch == KEY_F(10))
            break;
    }
}