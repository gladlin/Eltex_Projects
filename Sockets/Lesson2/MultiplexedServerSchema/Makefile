CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -lrt

WAITER ?= select
OBJ = create_sockets.o server_work.o work_with_client.o wait_action.o

all: start_server client_tcp client_udp

start_server: server/main.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

wait_action.o: server/wait_actions/$(WAITER).c server/server.h
	$(CC) $(CFLAGS) -c $< -o $@

create_sockets.o: server/create_sockets.c server/server.h server_client.h
	$(CC) $(CFLAGS) -c $< -o $@

server_work.o: server/server_work.c server/server.h server_client.h
	$(CC) $(CFLAGS) -c $< -o $@

work_with_client.o: server/work_with_client.c server/server.h server_client.h
	$(CC) $(CFLAGS) -c $< -o $@

client_tcp: clients/client_tcp.c server_client.h clients/clients.h
	$(CC) $(CFLAGS) $< -o $@

client_udp: clients/client_udp.c server_client.h clients/clients.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o start_server client_tcp client_udp
