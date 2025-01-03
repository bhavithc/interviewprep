// query the running msg queues 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
    // struct msqid_ds info;
    if (msgctl(1, IPC_RMID, NULL) < 0) {
        perror("Failed to get stat of msg");
        exit(EXIT_FAILURE);
    }

    printf("Message queue ID: %d removed !\n", 1);
    return 0;
}