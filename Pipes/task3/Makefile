CC = gcc
FLAGS = -Wall -Wextra -Werror

all: start_pipe.o execute_command.o execute_pipeline.o
	${CC} ${FLAGS} main.c start_pipe.o execute_pipeline.o execute_command.o -o conveyorPipe
	
start_pipe.o:
	${CC} ${FLAGS} -c start_pipe.c 

execute_command.o:
	${CC} ${FLAGS} -c execute_command.c 

execute_pipeline.o:
	${CC} ${FLAGS} -c execute_pipeline.c 

clear:
	rm *.o conveyorPipe

start: all
	./conveyorPipe