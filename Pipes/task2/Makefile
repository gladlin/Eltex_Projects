CC = gcc
FLAGS = -Wall -Wextra -Werror

client: 
	${CC} ${FLAGS} client.c -o client

server:
	${CC} ${FLAGS} server.c -o clienservert

clear:
	rm *.o clientServerWork

start_client: client
	./client

start_server: server
	./server