#include "ui.h"

static WINDOW *chat_win, *user_win, *input_win;
static int screen_rows, screen_cols;
static int chat_win_rows, chat_win_cols;
static int user_win_cols;

void init_ui(void) {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);
    getmaxyx(stdscr, screen_rows, screen_cols);
    
    user_win_cols = screen_cols / 4;
    chat_win_cols = screen_cols - user_win_cols;
    chat_win_rows = screen_rows - UI_INPUT_HEIGHT;
    
    chat_win = newwin(chat_win_rows, chat_win_cols, 0, 0);
    user_win = newwin(chat_win_rows, user_win_cols, 0, chat_win_cols);
    input_win = newwin(UI_INPUT_HEIGHT, screen_cols, chat_win_rows, 0);
    
    scrollok(chat_win, TRUE);
    
    box(user_win, 0, 0);
    box(input_win, 0, 0);
    
    wrefresh(chat_win);
    wrefresh(user_win);
    wrefresh(input_win);
}

void cleanup_ui(void) {
    delwin(chat_win);
    delwin(user_win);
    delwin(input_win);
    endwin();
}

void add_message(const char *username, const char *msg) {
    if (strcmp(username, "system message") == 0) {
        wprintw(chat_win, "%s\n", msg);
    } else {
        wprintw(chat_win, "%s: %s\n", username, msg);
    }
    wrefresh(chat_win);
}

void update_user_list(char users[][32], int user_count) {
    werase(user_win);
    box(user_win, 0, 0);
    mvwprintw(user_win, 0, 1, "Users");
    for (int i = 0; i < user_count && i < (chat_win_rows - 1); i++) {
        mvwprintw(user_win, i + 1, 1, "%s", users[i]);
    }
    wrefresh(user_win);
}

void get_input(char *buffer, int max_len) {
    werase(input_win);
    box(input_win, 0, 0);
    mvwprintw(input_win, 1, 1, "Enter message: ");
    wrefresh(input_win);
    echo();
    wgetnstr(input_win, buffer, max_len);
    noecho();
}
