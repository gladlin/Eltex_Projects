GCC = gcc
FLAGS = -Wall -Wextra -Werror

all: task1 task2 task3

handleSignal: task1/handleSignal.c
	${GCC} ${FLAGS} task1/handleSignal.c -o handler

sendSignal: task1/sendSignal.c
	${GCC} ${FLAGS} task1/sendSignal.c -o sender

handlerBlock: task2/handlerBlock.c
	${GCC} ${FLAGS} task2/handlerBlock.c -o handlerBlock

eventLoop: task3/eventLoop.c
	${GCC} ${FLAGS} task3/eventLoop.c -o eventLoop

task1: handleSignal sendSignal
task2: handlerBlock sendSignal
task3: eventLoop sendSignal

clear:
	rm handler sender handlerBlock eventLoop