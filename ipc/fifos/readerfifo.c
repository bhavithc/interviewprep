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
    if ((fd = open(pathName, O_RDONLY)) < 0) {
        perror("Failed to open the file");
        exit(EXIT_FAILURE);
    }

    char buff[20] = {0, };

    while (1) {
        int bytesRead = read(fd, buff, sizeof(buff));
        printf("%s", buff);
        if (bytesRead == 0) { 
            break;
        }
        memset(buff, 0, sizeof(buff));
    }

    exit(EXIT_SUCCESS);
}