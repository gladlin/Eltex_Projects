CC = gcc
FLAGS = -Wall -Wextra -Werror

all: unnamePipe.o
	${CC} ${FLAGS} main.c unnamePipe.o -o sendReceiveMessage
	
unnamePipe.o:
	${CC} ${FLAGS} -c unnamePipe.c 

clear:
	rm *.o sendReceiveMessage

start: all
	./sendReceiveMessage