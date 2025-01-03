#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void print2OnesTable(void)
{
    int i = 0;
    for (i = 1; i <= 10; i++) {
        printf("2 x %d = %d\n", i, 2 * i);
        // usleep(1000 * 200);
    }

    // sleep(1);
}


int main()
{

    pid_t pid = fork();
    if (pid == 0) {
        print2OnesTable();
        exit(EXIT_SUCCESS);
    } else {
        printf("Child running at %d pid \n", pid);
        printf("Parent process !\n");
        sleep(20);
        int status = -1;
        pid_t child = wait(&status);
        printf("Child (%d) exited with status : %d \n", child, status);

        // WIFEXITED(status);
    }

    return EXIT_SUCCESS;
}