#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define SERVER_QUEUE_NAME "/mq-server"
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main()
{
    // queue descriptor
    mqd_t qd_server;
    mqd_t qd_client;

    long token_number = 1;
    fprintf(stdout, "Server: hello world\n");

    // message attribute
    struct mq_attr attr; 
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ( (qd_server = mq_open(SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, 0664, &attr)) < 0) {
        perror("Failed to createe mq_open");
        exit(EXIT_FAILURE);
    }

    char in_buffer[MSG_BUFFER_SIZE] = {0, };
    char out_buffer[MSG_BUFFER_SIZE] = {0, };

    while (1) {
        // get oldest message with high priority
        if (mq_receive(qd_server, in_buffer, MSG_BUFFER_SIZE, NULL) < 0) {
            perror("Server: mq_receive");
            exit(EXIT_FAILURE);
        }

        fprintf(stdout, "Server: message recevied !\n");

        if ((qd_client = mq_open(in_buffer, O_WRONLY)) < 0) {
            perror("Server: unable to open client queque");
            continue;
        }

        // send reply to client 
        sprintf(out_buffer, "%ld", token_number);

        if (mq_send(qd_client, out_buffer, strlen(out_buffer) + 1, 0) < 0) {
            perror("Server: unable to send message to client");
            continue;
        }

        printf("Server: response sent to client \n");
        token_number++;
    }
}