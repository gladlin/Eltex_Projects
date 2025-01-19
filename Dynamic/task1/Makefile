
all: phonebook valgrind
phonebook:
	gcc -Wall -Wextra -Werror *.c -o phonebook -g
valgrind: phonebook
	valgrind --leak-check=full ./phonebook
clean:
	rm -rf *.o ./phonebook
