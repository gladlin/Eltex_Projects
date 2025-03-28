CC = gcc
FLAGS = -Wall -Wextra -Werror
THREAD_FLAGS = -pthread

all: print_thread.o
	${CC} ${FLAGS} ${THREAD_FLAGS} main.c print_thread.o -o printThread
	
print_thread.o:
	${CC} ${FLAGS} -c print_thread.c 

start: all
	./printThread

clear:
	rm *.o printThread