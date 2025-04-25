CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
OBJ = servers.o additional.o

all: start_server client

start_server: server/main.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

servers.o: server/servers.c server/server.h server_client.h
	$(CC) $(CFLAGS) -c $< -o $@

additional.o: server/additional.c server/server.h server_client.h
	$(CC) $(CFLAGS) -c $< -o $@

client: client.c server_client.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o start_server client
