GCC = gcc
FLAGS = -Wall -Werror -Wextra

all: server client

server: server.c broadcast.h
	${GCC} ${FLAGS} server.c -o server

client: client.c broadcast.h
	${GCC} ${FLAGS} client.c -o client

clean:
	rm server client