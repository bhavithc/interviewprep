#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define SHOW_CREDS() do {           \
    printf("RUID: %d, EUID: %d\n"   \
           "RGID: %d, EGID: %d\n",  \
           getuid(), geteuid(),     \
           getgid(), getegid());    \
    } while (0)                 

int main()
{
    SHOW_CREDS();

    if (setuid(0) == -1) {
        printf("Failed to get root previlege !\n");
    }

    system("/usr/bin/bash");

    printf("I am in new shell !\n");

    SHOW_CREDS();

    return EXIT_SUCCESS;
}