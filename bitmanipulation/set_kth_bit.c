#include <stdio.h>
#include "decimal_to_int.h"

void set_ith_bit(int* nr, const int pos)
{
    int mask = (1 << pos);
    *nr = (*nr | mask);
}

#define NR 16
#define POS 1

int main()
{
    int a = NR;
    printf("before\n");
    printInDecimal(a);
    set_ith_bit(&a, POS);
    printf("after setting pos %d\n", POS);
    printInDecimal(a);
}