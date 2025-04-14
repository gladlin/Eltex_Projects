#ifndef CLIENT_H
#define CLIENT_H

#include "../chat.h"
#include "../ncurses/ui.h"


extern int flag_is_connected;
extern struct message *shm_base_message;

int connectToChat();
int start_thread_client(char *username);
void *getMessages();
void *sendMessage(void *arg);
void *getUserList();

#endif