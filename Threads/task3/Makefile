CC = gcc
FLAGS = -Wall -Wextra -Werror
THREAD_FLAGS = -pthread

all: buyer.o provider.o start_shop.o
	${CC} ${FLAGS} ${THREAD_FLAGS} main.c buyer.o provider.o start_shop.o -o createShop
	
buyer.o:
	${CC} ${FLAGS} ${THREAD_FLAGS} -c buyer.c 

provider.o:
	${CC} ${FLAGS} ${THREAD_FLAGS} -c provider.c 

start_shop.o:
	${CC} ${FLAGS} ${THREAD_FLAGS} -c start_shop.c 

clear:
	rm *.o createShop

start: all
	./createShop