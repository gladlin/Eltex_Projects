CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

server: server.c systemV.h
	$(CC) $(CFLAGS) -o server server.c

client: client.c systemV.h
	$(CC) $(CFLAGS) -o client client.c

start_server: server
	./server

start_client: client
	./client

clean:
	rm -f server client