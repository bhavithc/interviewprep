#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// 0 - read end 
// 1 - write end
int main()
{
    int fd[2] = {-1, -1};
    pid_t pid = -1;
    const char* msg = "Bhavith C";

    if (pipe(fd) < 0) {
        perror("Failed to create pipe!\n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0) {
        close (fd[0]);
        close (fd[1]);
        perror("Failed to create fork\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("Child process \n");
        close(fd[0]);
        fd[0] = -1;
        write(fd[1], msg, strlen(msg));
    } else {
        printf("Parent process\n");
        close (fd[1]);
        fd[1] = -1;
        char buf[100] = {0, };
        read(fd[0], buf, strlen(msg));
        printf("Message from child: %s\n", buf);
        waitpid(pid, 0, 0);
    }

    exit(EXIT_SUCCESS);
}