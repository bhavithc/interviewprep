#ifndef __DEC__
#define __DEC__

#include <stdio.h>
void printInDecimal(int nr)
{
    int bytes[sizeof(int)];

    int i = 0;
    while (nr) {
        bytes[i] = nr % 2;
        nr = nr / 2;
        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        printf("%d ", bytes[j]);
    }
    printf("\n");
}

#endif