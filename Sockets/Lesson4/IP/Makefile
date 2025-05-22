GCC = gcc
FLAGS = -Wall -Wextra -Werror -g

all: server client

server: server.c ip_raw.h
	${GCC} ${FLAGS} server.c -o server

client: client.c ip_raw.h
	${GCC} ${FLAGS} client.c -o client

clear:
	rm client server