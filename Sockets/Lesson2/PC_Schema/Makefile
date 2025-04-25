CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -lrt
OBJ = listen_server.o additional.o child_servers.o pool.o

all: start_server client

start_server: server/main.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

listen_server.o: server/listen_server.c server/server.h server_client.h
	$(CC) $(CFLAGS) -c $< -o $@

additional.o: server/additional.c server/server.h server_client.h
	$(CC) $(CFLAGS) -c $< -o $@

child_servers.o: server/child_servers.c server/server.h server_client.h
	$(CC) $(CFLAGS) -c $< -o $@

pool.o: server/pool.c server/server.h server_client.h
	$(CC) $(CFLAGS) -c $< -o $@

client: client.c server_client.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o start_server client
