// query the running msg queues 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
    struct msqid_ds info;
    if (msgctl(1, IPC_STAT, &info) < 0) {
        perror("Failed to get stat of msg");
        exit(EXIT_FAILURE);
    }

    printf("Message queue ID: %d\n", 1);
    printf("Permissions: %o\n", info.msg_perm.mode);
    printf("Messages: %lu\n", info.msg_qnum);
    printf("Bytes in queue: %lu\n", info.msg_cbytes);
    return 0;
}