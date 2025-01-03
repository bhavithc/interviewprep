#include <stdio.h>
#include "decimal_to_int.h"


int pop_count(const int nr)
{
    int n = nr;
    int cnt = 0;
    while (n) {
        n = n & (n - 1);
        cnt++;
    }

    return cnt;
}

int main()
{
    int i = 0;
    for (i = 0; i < 20; i++) {
        printInDecimal(i);
        printf("nr of bit set is %d\n\n", pop_count(i));
    }
    return 0;
}