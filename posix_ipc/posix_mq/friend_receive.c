#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MQ_NAME "/friends"
#define MAX_MSG_SIZE 100


int main()
{
    mqd_t server_qd;
    struct mq_attr attr;

    server_qd = mq_open(MQ_NAME, O_RDONLY);
    if (server_qd < 0) {
        perror("client: mq_open");
        exit(EXIT_FAILURE);
    }

    int iter = 0;
    for (iter = 0; iter < 10; iter++) {

        if (mq_getattr(server_qd, &attr) < 0) {
            perror("Client: mq_getattr");
            continue;
        }

        fprintf(stdout, "Current message: %ld\n", attr.mq_curmsgs);
        fprintf(stdout, "Flag: %ld\n", attr.mq_flags);
        fprintf(stdout, "Max msg: %ld\n", attr.mq_maxmsg);
        fprintf(stdout, "Msg size: %ld\n", attr.mq_msgsize);

        char buffer[MAX_MSG_SIZE] = {0, };
        if (mq_receive(server_qd, buffer, MAX_MSG_SIZE, 0) < 0) {
            perror("Client: mq_receive");
            exit(EXIT_FAILURE);
        }
        printf("msg: %s\n\n", buffer);
    }

    mq_close(server_qd);
    exit(EXIT_SUCCESS);
}