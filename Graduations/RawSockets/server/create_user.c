#include "server.h"

extern struct echo_messages *head;

struct echo_messages *create_user(struct sockaddr_in *client) 
{
    struct echo_messages *current = head;
    while (current != NULL) 
    {
        if (current->client_addr.sin_addr.s_addr == client->sin_addr.s_addr &&
            current->client_addr.sin_port == client->sin_port) 
            return current;

        current = current->next_client;
    }

    struct echo_messages *new_client = malloc(sizeof(struct echo_messages));
    if (new_client == NULL) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_client->client_addr = *client;
    new_client->messages = 0;
    new_client->next_client = head;
    head = new_client;
    return new_client;
}