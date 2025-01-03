#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define SHOW_CREDS() do {           \
    printf("RUID: %d, EUID: %d\n"   \
           "RGID: %d, EGID: %d\n",  \
           getuid(), geteuid(),     \
           getgid(), getegid());    \
    } while (0)                 


int main()
{
    SHOW_CREDS(); 
    if (getuid() == 0) {
        printf("Now program is running as root !\n");
    }

    exit(EXIT_SUCCESS);
}