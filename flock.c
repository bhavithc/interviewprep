#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main()
{
    int i = 0;
    int fd = open("bhavith.txt", O_CREAT | O_APPEND | O_WRONLY, 0777);
    if (fd < 0) {
        printf("Failed to create or open the file, %s", strerror(errno));
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == 0) {
        const char* pName = "Children\n";
        for (i = 0; i < 20; i++) {
            if (write(fd, pName, strlen(pName)) != (ssize_t)(strlen(pName))) {
                perror("Failed to write in child");
                break;
            }
            usleep(1000 * 10);
        }
        exit(EXIT_SUCCESS);
    } else {
        const char* pName = "Parent\n";
        for (i = 0; i < 20; i++) {
            if (write(fd, pName, strlen(pName)) != (ssize_t)(strlen(pName))) {
                perror("Failed to write parent");
                break;
            }
            usleep(1000 * 10);
        }
        wait(0);
    }

    printf("Closing fd's\n");
    close(fd);

    return 0;
}