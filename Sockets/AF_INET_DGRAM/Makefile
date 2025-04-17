GCC = gcc
FLAGS = -Wall -Wextra -Werror

all: server client

server: server.c af_inet_dgram.h
	${GCC} ${FLAGS} server.c -o server

client: client.c af_inet_dgram.h
	${GCC} ${FLAGS} client.c -o client

clear:
	rm client server