#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main()
{
    const char* pathName = "./myfifo";
    struct stat statBuf;
    int fifoCreated = 0;
    
    // check already fifo exists
    if (stat(pathName, &statBuf) == 0) {
        if (S_ISFIFO(statBuf.st_mode)) {
            fprintf(stdout, "WARNING: fifo: %s already exist\n", pathName);
            fifoCreated = 1;
        } else {
            fprintf(stdout, "ERROR: file (%s) already exist but its not a fifo\n", pathName);
        }

    } else {

        if (mkfifo(pathName, 0666 | S_IFIFO) < 0) {
            fprintf(stdout, "Failed to create fifo: %s [%s]\n", pathName, strerror(errno));
        } else {
            fifoCreated = 1;
        }

    }

    if (fifoCreated) {
        fprintf(stdout, "fifo %s created successfully!\n", pathName);
    } else {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}