CC = gcc
FLAGS = -Wall -Wextra -Werror

all: libcalculator.so calc

libcalculator.so: add.o sub.o mul.o div.o
	$(CC) -shared -o libcalculator.so add.o sub.o mul.o div.o

add.o: function/add.c
	$(CC) $(FLAGS) -fPIC -c function/add.c -o add.o

sub.o: function/sub.c
	$(CC) $(FLAGS) -fPIC -c function/sub.c -o sub.o

mul.o: function/mul.c
	$(CC) $(FLAGS) -fPIC -c function/mul.c -o mul.o

div.o: function/div.c
	$(CC) $(FLAGS) -fPIC -c function/div.c -o div.o	

calc:
	$(CC) $(FLAGS) main.c -ldl -o calc

clean:
	rm -f *.o libcalculator.so calc