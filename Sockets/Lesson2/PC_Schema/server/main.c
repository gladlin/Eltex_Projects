#include "server.h"

volatile sig_atomic_t stop = 0;

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_CLIENTS;
    attr.mq_msgsize = sizeof(struct sockaddr_in);
    attr.mq_curmsgs = 0;

    mqd_t client_mq = mq_open(MQ_NAME, O_CREAT | O_RDWR | O_EXCL, 0666, &attr);
    if (client_mq == (mqd_t)-1) {
        perror("mq_open server");
        exit(1);
    }

    listen_server(client_mq);
    return 0;
}