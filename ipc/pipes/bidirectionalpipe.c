#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    const char* msgFromChild = "Message from child, hello parent";
    const char* msgFromParent = "Message from parent, hello child";

    int pipe1Fd[2] = {-1, -1};
    int pipe2Fd[2] = {-1, -1};
    pid_t pid = -1;

    if (pipe(pipe1Fd) < 0) {
        perror("Failed to create pipe1\n");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe2Fd) < 0) {
        perror("Failed to create pipe2\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    switch (pid)
    {
    case -1:
        perror("Failed to create fork!\n");
        exit(EXIT_FAILURE);
    case 0:
        printf("Child process \n");
        // prepare first pipe
        // close read end
        close(pipe1Fd[0]);
        pipe1Fd[0] = -1;
        // child can only write here 
        write(pipe1Fd[1], msgFromChild, strlen(msgFromChild));

        // prepare second pipe
        // close write end 
        close(pipe2Fd[1]);
        pipe2Fd[1] = -1;
        // child can only read here 
        char buf[100] = {0,};
        read(pipe2Fd[0], buf, strlen(msgFromParent));
        printf("%s\n", buf);

        break;
    default:
        printf("Parent process\n");
        // prepare first pipe
        // close write end
        close(pipe1Fd[1]);
        pipe1Fd[1] = -1;
        // parent can only read here 
        char buf2[100] = {0,};
        read(pipe1Fd[0], buf2, strlen(msgFromChild));
        printf("%s\n", buf2);

        // prepare second pipe
        // close read end 
        close(pipe2Fd[0]);
        pipe2Fd[0] = -1;
        // parent can only write here
        write(pipe2Fd[1], msgFromParent, strlen(msgFromParent));

        if (wait(0) < 0) {
            perror("Wait failed \n");
        }
        break;
    }

}