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

    struct message msg[3];

    // read all the messages
    for (msgIter = 0; msgIter < 3; msgIter++) {
        if (msgrcv(msgId, &msg[msgIter], sizeof(struct message), 0, 0) < 0) {
            fprintf(stdout, "Failed to read message: %d [%s]\n", msg[msgIter].type, strerror(errno));
            break;
        } else {
            fprintf(stdout, "Message read: %d - %s\n", msg[msgIter].type, msg[msgIter].message);
        }
    }

    exit(EXIT_SUCCESS);
}