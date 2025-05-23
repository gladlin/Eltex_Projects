GCC = gcc
FLAGS = -Wall -Wextra -Werror -g

all: server client

server: server.c ethernet_raw.h
	${GCC} ${FLAGS} server.c -o server

client: client.c ethernet_raw.h
	${GCC} ${FLAGS} client.c -o client

clear:
	rm client server