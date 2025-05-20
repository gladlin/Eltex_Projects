GCC = gcc
FLAGS = -Wall -Wextra -Werror

all: server client

server: server.c udp_raw.h
	${GCC} ${FLAGS} server.c -o server

client: client.c udp_raw.h
	${GCC} ${FLAGS} client.c -o client

clear:
	rm client server