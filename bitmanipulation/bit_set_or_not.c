#include <stdio.h>
#include "decimal_to_int.h"


int bit_set_or_not(int nr, int pos)
{
    return (nr & (1 << pos)) != 0;
}

void print_msg(const int is_set, const int pos)
{
    if (is_set) {
        printf("%d bit is set !\n", pos);
    } else {
        printf("%d bit is not set!\n", pos);
    }
}

#define NR 17
#define POS 1

int main()
{
    printInDecimal(NR);
    print_msg(bit_set_or_not(NR, POS), POS);
    return 0;
}
