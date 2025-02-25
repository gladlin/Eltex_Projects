CC = gcc
FLAGS = -Wall -Wextra -Werror

all: createSecondProcess.o
	${CC} ${FLAGS} main.c createSecondProcess.o -o twoProcess
createSecondProcess.o:
	${CC} ${FLAGS} -c createSecondProcess.c 

start: all
	./twoProcess

clear:
	rm *.o twoProcess