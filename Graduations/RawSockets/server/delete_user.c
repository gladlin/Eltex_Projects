#include "server.h"

extern struct echo_messages *head;

void delete_user(struct echo_messages *client) 
{
    if (client == head) 
    {
        head = head->next_client;
        memset(client, 0, sizeof(&client));
        free(client);
        return;
    }

    struct echo_messages *prev = head;
    while (prev->next_client && prev->next_client != client) 
    {
        prev = prev->next_client;
    }

    if (prev->next_client == client) 
    {
        prev->next_client = client->next_client;
        free(client);
    }
}