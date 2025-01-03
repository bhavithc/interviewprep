#include <stdio.h>
#include "decimal_to_int.h"

void toggle_ith_bit(int* nr, const int pos)
{
    const int mask =  (1 << pos);
    *nr = (*nr ^ mask);
}

#define NR 10
#define POS 3

int main()
{
    int a = NR;
    printf("before\n");
    printInDecimal(a);
    toggle_ith_bit(&a, POS);
    printf("after toggle at pos %d\n", POS);
    printInDecimal(a);
}