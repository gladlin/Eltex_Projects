CC = gcc
FLAGS = -Wall -Wextra -Werror

all: read.o write.o
	${CC} ${FLAGS} main.c read.c write.c -o readWriteFile

read.o:
	${CC} ${FLAGS} -c read.c

write.o:
	${CC} ${FLAGS} -c write.c

start: all
	./readWriteFile

clear:
	rm readWriteFile *.o