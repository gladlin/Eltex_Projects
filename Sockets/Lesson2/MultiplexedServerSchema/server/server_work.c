#include "server.h"

void start_server()
{
    printf("Сервер начинает свою работу\n");
    int tcp_fd, udp_fd;
    struct sockaddr_in tcp_sock, udp_sock;
    if(create_tcp_socket(&tcp_fd, &tcp_sock) == -1)
    {
        perror("create_socket tcp");
        return;
    }
    if(create_socket_udp(&udp_fd, &udp_sock) == -1)
    {
        perror("create_socket udp");
        return;
    }
    
    wait_action(tcp_fd, udp_fd);
    
    close(tcp_fd);
    close(udp_fd);

}