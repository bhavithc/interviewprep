#include <stdio.h>
#include <stdlib.h>

int main()
{
    int success = system("/usr/bin/bash");
    if (success == 0) {
        printf("success \n");
    } else {
        printf("failed !\n");
    }

    return 0;
}