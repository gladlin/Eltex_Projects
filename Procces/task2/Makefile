CC = gcc
FLAGS = -Wall -Wextra -Werror

all: libmanyProcess.a
	${CC} ${FLAGS} main.c -L. -lmanyProcess -o createProcess
process1.o:
	${CC} ${FLAGS} -c workProcess1.c 

process2.o:
	${CC} ${FLAGS} -c workProcess2.c

waitProcess.o:
	${CC} ${FLAGS} -c waitProcess.c

mainProcess.o:
	${CC} ${FLAGS} -c mainProcess.c

libmanyProcess.a: workProcess1.o workProcess2.o waitProcess.o mainProcess.o
	ar rcs libmanyProcess.a workProcess1.o workProcess2.o waitProcess.o mainProcess.o

start: all
	./createProcess

clear:
	rm *.o *.a createProcess