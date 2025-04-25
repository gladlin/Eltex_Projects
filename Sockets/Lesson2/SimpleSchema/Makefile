GCC = gcc
FLAGS = -Wall -Werror -Wextra -pthread

all: server client

server: server.c server_client.h
	${GCC} ${FLAGS} server.c -o server

client: client.c server_client.h
	${GCC} ${FLAGS} client.c -o client

clear:
	rm -f *.o server client
