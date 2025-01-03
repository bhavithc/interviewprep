#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MQ_NAME "/friends"


int main()
{
    mqd_t server_qd;
    struct mq_attr attr;

    attr.mq_curmsgs = 0;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
 
    server_qd =  mq_open(MQ_NAME, O_RDWR | O_CREAT, 0664, &attr);
    if (server_qd < 0) {
        perror("Server: mq_open");
        exit(EXIT_FAILURE);
    }

    int iter = 0;
    for (iter = 0; iter < 5; iter++) {
        char msg[100] = {0, };
        sprintf(msg, "Message %d", iter);
        if (mq_send(server_qd, msg, 100, 0) < 0) {
            perror("Server: mq_send");
            exit(EXIT_FAILURE);
        }
        printf("%s sent succefully !\n", msg);
    }

    mq_close(server_qd);
    exit(EXIT_SUCCESS);
}
