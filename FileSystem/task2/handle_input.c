#include "mc.h"

int handle_input(int ch, Panel *active) {
    switch (ch) {
        case KEY_UP:
            if (active->current > 0) active->current--;
            break;
        case KEY_DOWN:
            if (active->current < active->count - 1) active->current++;
            break;
        case 9: // Tab
            return 1;
        case 10: // Enter
            change_dir(active);
            break;
    }
    return 0;
}