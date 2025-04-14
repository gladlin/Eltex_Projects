#ifndef SERVER_H
#define SERVER_H

#include "../chat.h"
#include "../ncurses/ui.h"

extern char users[MAX_USERS][MAX_USERNAME];
extern int user_count;
extern int server_running;

int start_server();
int start_thread(char *shm_base_username, struct message *shm_base_message);
void *watch_users(void *arg);
void *watch_messages(void *arg);

#endif