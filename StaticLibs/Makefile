CC = gcc
FLAGS = -Wall -Wextra -Werror

all: libfunc
	${CC} ${FLAGS} main.c -L . -lcalculator -o calc

libfunc: add.o sub.o mul.o div.o
	ar rc libcalculator.a *.o

add.o:
	${CC} ${FLAGS} function/add.c -c

sub.o:
	${CC} ${FLAGS} function/sub.c -c

mul.o:
	${CC} ${FLAGS} function/mul.c -c

div.o:
	${CC} ${FLAGS} function/div.c -c

clean:
	rm *.o libcalculator.a