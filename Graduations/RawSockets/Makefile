GCC = gcc
FLAGS = -Wall -Wextra -Werror
OBJDIR = obj

all: client server

server: server/main.c echo_server_client.h ${OBJDIR}/create_user ${OBJDIR}/delete_user ${OBJDIR}/send_message
	${GCC} ${FLAGS} server/main.c ${OBJDIR}/*.o -o server_start

${OBJDIR}/create_user: server/create_user.c echo_server_client.h
	${GCC} ${FLAGS} server/create_user.c -c -o ${OBJDIR}/create_user.o

${OBJDIR}/delete_user: server/delete_user.c echo_server_client.h
	${GCC} ${FLAGS} server/delete_user.c -c -o ${OBJDIR}/delete_user.o

${OBJDIR}/send_message: server/send_message.c echo_server_client.h
	${GCC} ${FLAGS} server/send_message.c -c -o ${OBJDIR}/send_message.o

start_server: server
	./server_start

client: client/main.c echo_server_client.h
	${GCC} ${FLAGS} client/main.c -o client_start

start_client: client
	./client_start

clean:
	rm server_start client_start ${OBJDIR}/*.o