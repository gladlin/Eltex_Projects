CC = gcc
FLAGS = -Wall -Wextra -Werror

all: draw.o handle_input.o init_curses.o run.o work_with_dir.o
	${CC} ${FLAGS} main.c draw.c handle_input.c init_curses.c run.c work_with_dir.c -o mc -lncurses

draw.o:
	${CC} ${FLAGS} -c draw.c 

handle_input.o:
	${CC} ${FLAGS} -c handle_input.c 

init_curses.o:
	${CC} ${FLAGS} -c init_curses.c 

run.o:
	${CC} ${FLAGS} -c run.c

work_with_dir.o:
	${CC} ${FLAGS} -c work_with_dir.c

start: all
	./mc

clear:
	rm mc *.o