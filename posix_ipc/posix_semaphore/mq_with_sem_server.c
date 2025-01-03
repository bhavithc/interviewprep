#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    sem_t* sem = sem_open(SERVER_SEM, O_WRONLY | O_CREAT, 0666, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    sem_t* client_sem = sem_open(CLIENT_SEM, O_RDWR | O_CREAT, 0666, 0);
    if (client_sem == SEM_FAILED) {
        perror("server: client sem_open");
        exit(EXIT_FAILURE);
    }

    // open the mq
    mqd_t server_qd = mq_open("/bhavith", O_WRONLY | O_CREAT, 0666, &attr);
    if (server_qd < 0) {
        perror("server: mq_open");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for client to start\n");
    if (sem_wait(client_sem) < 0) {
        perror("server: sem_wait");
        exit(EXIT_FAILURE);
    }

    int iter = 0;
    for (iter = 0; iter < 5; iter++) {
        
        // send message
        char buf[20] = {0, };
        sprintf(buf, "message: %d", iter);
        printf("sending \"%s\"\n", buf);
        if (mq_send(server_qd, buf, 20, 0) < 0) {
            perror("server: mq_send");
            break;
        }

        printf("message sent: %s\n", buf);

        // notify 
        printf("notified \n");
        if (sem_post(sem) < 0) {
            perror("server: sem_post failed");
        }

        // wait for ack
        printf("waiting for ack \n");
        if (sem_wait(client_sem) < 0) {
            perror("server: sem_wait");
        }
    }

    mq_close(server_qd);
    sem_close(sem);
    sem_close(client_sem);
    sem_unlink("bhavith");
    exit(EXIT_SUCCESS);
}