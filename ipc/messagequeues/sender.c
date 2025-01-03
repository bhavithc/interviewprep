#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct message 
{
    int type;
    char message[512];
};


int main()
{
    int msgIter = 0;
    key_t key = 10;
    // get message queque
    const int msgId = msgget(key, IPC_CREAT | 0664);
    if (msgId == -1) {
        printf("Failed to get the message queque: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("Message queue created with id: %d\n", msgId);

    // Prepare 3 messages 
    struct message msg[3];
    msg[0].type = 1;
    strcpy(msg[0].message, "Message 1");

    msg[1].type = 2;
    strcpy(msg[1].message, "Message 2");

    msg[2].type = 3;
    strcpy(msg[2].message, "Message 3");

    for (msgIter = 0; msgIter < 3; msgIter++) {
        if (msgsnd(msgId, &msg[msgIter], sizeof(struct message), 0) < 0) {
            fprintf(stdout, "Failed to send message: %d [%s]\n", msg[msgIter].type, strerror(errno));
            break;
        } else {
            fprintf(stdout, "Message: %d sent successfully !\n", msg[msgIter].type);
        }
    }

    exit(EXIT_SUCCESS);
}