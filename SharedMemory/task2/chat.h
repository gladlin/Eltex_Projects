#ifndef CHAT_H
#define CHAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>


#define MAX_USERS 10
#define MAX_LENGHT_MESSAGE 256
#define MAX_MESSAGES 128
#define MAX_USERNAME 32
#define SHM_USER "shared_user"
#define SHM_MESSAGE "shared_message"

struct message
{
    char message[MAX_LENGHT_MESSAGE];
    char username[MAX_USERNAME];
};

extern struct message *shm_base_message;

#endif