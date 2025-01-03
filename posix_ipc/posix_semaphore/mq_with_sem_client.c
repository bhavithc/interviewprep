#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

#define SERVER_SEM "/server"
#define CLIENT_SEM "/client"


void printValue(int seq, sem_t* sem)
{
    int value = -1;
    sem_getvalue(sem, &value);
    printf("%d - value: %d\n", seq, value);
}

int main()
{
    struct mq_attr attr;
    attr.mq_curmsgs = 0;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;

    // open semaphore
    sem_t* sem = sem_open(CLIENT_SEM, O_RDWR);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    sem_t* server_sem = sem_open(SERVER_SEM, O_RDWR);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }


    // open the mq
    mqd_t server_qd = mq_open("/bhavith", O_RDONLY, 0666, &attr);
    if (server_qd < 0) {
        perror("client: mq_open");
        exit(EXIT_FAILURE);
    }

    // notify client is ready
    printf("notify server that client is ready!\n");
    if (sem_post(sem) < 0) {
        perror("client: sem_post");
        exit(EXIT_FAILURE);
    }

    int iter = 0;
    for (iter = 0; iter < 5; iter++) {
        // wait for message
        if (sem_wait(server_sem) < 0) {
            perror("client: sem_wait");
        }
        
        struct mq_attr attr;
        if (mq_getattr(server_qd, &attr) == -1) {
            perror("mq_getattr");
            exit(EXIT_FAILURE);
        }

        printf("reading %ld bytes\n", attr.mq_msgsize);
        // read message
        char buf[20] = {0, };
        if (mq_receive(server_qd, buf, attr.mq_msgsize, 0) < 0) {
            perror("client: mq_receive");
            printf("%s\n", buf);
            break;
        }
        printf("received: %s\n", buf);

        // notify done
        if (sem_post(sem) < 0) {
            perror("client: sem_post failed");
        }

    }
    
    mq_close(server_qd);
    sem_close(sem);
    sem_close(server_sem);
    exit(EXIT_SUCCESS);
}