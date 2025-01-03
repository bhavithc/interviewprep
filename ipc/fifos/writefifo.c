#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main()
{
    const char* pathName = "./myfifo";
    int fd = -1;

    if ((fd = open(pathName, O_WRONLY)) < 0){
        perror("Failed to open the file");
        exit(EXIT_FAILURE);
    }


    const char* buf = "Bhavith C, hello from the writer, lets see the size of the file after write";

    printf("We are writing %ld bytes\n", strlen(buf));

    const int cnt = write(fd, buf, strlen(buf));
    printf("Successfully written %d bytes \n", cnt);

    return 0;
}