// similar to cat, map the given file to private memory and flush to stdout
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    if (argc == 1) {
        printf("usage error: ./a.out <file_to_print>\n");
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file!");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(argv[1], &sb) < 0) {
        perror("Stat failed !");
        close(fd);
        fd = -1;
        exit(EXIT_FAILURE);
    }

    //sb.st_size;
    void* mem = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mem == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        fd = -1;
        exit(EXIT_FAILURE);
    }


    if (write(STDOUT_FILENO, mem, sb.st_size) == sb.st_size) {
        fprintf(stdout, "\ncontent written to stdout successfully !\n");
    }

    close (fd);
    fd = -1;

    // sleep(100); // give this sleep and check cat /proc/<pid>/maps to see the memory mapped proof

    sleep(20);
    if (munmap(mem, sb.st_size) < 0) {
        perror("munmap failed !");
        close (fd);
        fd = -1;
        exit(EXIT_FAILURE);
    }

    // sleep(10); // give this sleep and check again cat /proc/$(pidof a.out)/maps to see unmap worked
    exit(EXIT_SUCCESS);
}