GCC = gcc
FLAGS = -Wall -Wextra -Werror

all: client server

server: server/main.c echo_server_client.h
	${GCC} ${FLAGS} server/main.c -o server_start

start_server: server
	./server_start

client: client/main.c echo_server_client.h
	${GCC} ${FLAGS} client/main.c -o client_start

start_client: client
	./client_start

clean:
	rm server_start client_start