// ./a.out
// child started, value = 1
// In parent, value = 2

// create a child and parent using fork 
// child see default value as 1 and increase 1
// parent see the reflection

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_SIZE_BYTES 100

int main()
{
    int fd = open("/dev/zero", O_RDWR);
    if (fd == -1) {
        fprintf(stdout, "Failed to open /dev/zero %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    void* addr = mmap(NULL, MAX_SIZE_BYTES, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED) {
        close(fd); fd = -1;
        fprintf(stdout, "mmap failed %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    close(fd); fd = -1;

    // initialize addr with 1
    int* p = (int*)addr;
    *p = 1;

    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        fprintf(stderr, "Faile to fork: %s\n", strerror(errno));
        close (fd); fd = -1;
        exit(EXIT_FAILURE);
        break;
    case 0:
        fprintf(stdout, "Child started, value: %d\n", *((int*)addr));
        int* p = (void*)addr;
        (*p)++; // *p++ will not update the value back to *p
        msync(addr, MAX_SIZE_BYTES, MS_SYNC);
        munmap(addr, MAX_SIZE_BYTES);
        exit(EXIT_SUCCESS);
    default:
        wait(0);
        fprintf(stdout, "Inside parent, value: %d\n", *((int*)addr));
        munmap(addr, MAX_SIZE_BYTES);
        exit(EXIT_SUCCESS);
    }
    
}