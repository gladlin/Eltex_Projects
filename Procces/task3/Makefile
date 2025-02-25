CC = gcc
FLAGS = -Wall -Wextra -Werror

all: libexecute.a
	${CC} ${FLAGS} main.c -L. -lexecute -o executeFile

getParams.o:
	${CC} ${FLAGS} -c getParams.c 

execute.o:
	${CC} ${FLAGS} -c execute.c

libexecute.a: execute.o getParams.o
	ar rcs libexecute.a execute.o getParams.o 

start: all
	./executeFile

clear:
	rm *.o *.a executeFile