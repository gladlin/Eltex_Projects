CC = gcc
FLAGS = -Wall -Wextra -Werror
THREAD_FLAGS = -pthread

all: increment.o increment_mutex.o start_threads.o
	${CC} ${FLAGS} ${THREAD_FLAGS} main.c start_threads.o increment.o increment_mutex.o -o incrementVariable
	
increment.o:
	${CC} ${FLAGS} ${THREAD_FLAGS} -c increment.c 

increment_mutex.o:
	${CC} ${FLAGS} ${THREAD_FLAGS} -c increment_mutex.c 

start_threads.o:
	${CC} ${FLAGS} ${THREAD_FLAGS} -c start_threads.c 

clear:
	rm *.o incrementVariable

start: all
	./incrementVariable