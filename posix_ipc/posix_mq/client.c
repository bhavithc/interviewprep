#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define SERVER_QUEUE_NAME "/mq-server"
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10


int main()
{
    char client_queue_name[64] = {0, };
    mqd_t qd_server;
    mqd_t qd_client;

    sprintf(client_queue_name, "/mq-client-%d", getpid());

    struct mq_attr attr;
    attr.mq_curmsgs = 0;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;

    if ((qd_client = mq_open(client_queue_name, O_RDONLY | O_CREAT, 0664, &attr)) < 0) {
        perror("Client: mq_open (client)");
        exit(EXIT_FAILURE);
    }

    if ((qd_server =  mq_open(SERVER_QUEUE_NAME, O_WRONLY)) < 0){
        perror("Client: mq_open (server)");
        exit(EXIT_FAILURE);
    }


    char in_buffer[MSG_BUFFER_SIZE] = {0, };
    printf("Ask for token (press <ENTER>): ");
    char temp_buf[10] = {0, };

    while (fgets(temp_buf, 2, stdin)) {
        if (mq_send(qd_server, client_queue_name, strlen(client_queue_name) + 1, 0) < 0) {
            perror("Client: mq_send failed");
            continue;
        }

        if (mq_receive(qd_client, in_buffer, MSG_BUFFER_SIZE, NULL) < 0) {
            perror("Client: mq_received");
            exit(EXIT_FAILURE);
        }

        printf("Client: Token received from server: %s\n\n", in_buffer);
        printf("Ask for token (Press): ");
    }

    if (mq_close(qd_client) < 0) {
        perror("Client: mq_close");
        exit(EXIT_FAILURE);
    }

    if (mq_unlink(client_queue_name) < 0){
        perror("CLient: mq_unlink");
        exit(EXIT_FAILURE);
    }

    printf("Client: bye \n");
    exit(EXIT_SUCCESS);
}