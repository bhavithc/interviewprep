// 1. create an empty file of 1kb (1024) using dd command 
// 2. ./a.out <empty file> <message>
//     ex: a.out s.txt hello
//     out: start: 
//          written 'hello' to file 
// 3.      ./a.out s.txt good bye
//      out: start: hello
//                   written 'good bye` to file 
// 4. cat s.txt or od -c -w8 s.txt

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE 10

int main(int argc, char** argv)
{
    if ((argc == 1) || (argc == 2)) {
        fprintf(stdout, "Usage: ./a.out <mapfile> <message>\n");
        exit(EXIT_FAILURE);
    }

    const char* msg = "general info\n"
    "dd if=/dev/zero of=s.txt bs=1 count=1024\n"
    "od -c -w8 s.txt";
    printf("%s\n", msg);

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        fprintf(stdout, "Failed to open file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    void* map = mmap(0, MAX_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        fprintf(stderr, "Failed to create map: %s\n", strerror(errno));
        close (fd);
        fd = -1;
        exit(EXIT_FAILURE);
    }

    // we can close fd - no need to keep open since file is already mapped 
    close(fd);

    printf("start: %.*s\n", MAX_SIZE, (char*)map);

    if (strlen(argv[2]) >= MAX_SIZE) {
        fprintf(stderr, "Invalid size received, allowed size: %d\n", MAX_SIZE);
        close (fd);
        fd = -1;
        fprintf(stdout, "Unmapping the memory...\n");
        if (munmap(map, MAX_SIZE) < 0) {
            fprintf(stderr, "munmap failed: %s\n", strerror(errno));
            close (fd);
            fd = -1;
            exit(EXIT_FAILURE);
        }
    }

    (void)memset(map, 0, MAX_SIZE);
    (void)memcpy(map, argv[2], strlen(argv[2]));

    fprintf(stdout, "Written %s \n", argv[2]);

    if(msync(map, MAX_SIZE, MS_SYNC) < 0) {
        fprintf(stdout, "Failed to msync: %s\n", strerror(errno));
    }

    munmap(map, MAX_SIZE);
    exit(EXIT_SUCCESS);
}