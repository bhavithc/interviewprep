#include <stdio.h>
#include "decimal_to_int.h"

void clear_ith_bit(int* nr, const int pos)
{
    const int mask = ~(1 << pos);
    *nr = (*nr & mask);
}

#define NR 14
#define POS 2

int main()
{
    int a = NR;
    printf("before\n");
    printInDecimal(a);
    clear_ith_bit(&a, POS);
    printf("after clearning pos %d\n", POS);
    printInDecimal(a);
}