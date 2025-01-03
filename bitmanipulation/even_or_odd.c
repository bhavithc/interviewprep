#include <stdio.h>
#include "decimal_to_int.h"

void is_even(const int nr)
{
    if (nr & 1) {
        printf("%d is odd \n", nr);
    } else {
        printf("%d is even \n", nr);
    }
}

int main()
{
    int i = 0;
    for (i = 0; i < 20; i++) {
        is_even(i);
    }
}