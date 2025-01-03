#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void decimalToBin(const int nr)
{
    const int size = sizeof(int) * 8;
    int bytes[size];
    memset(bytes, 0, sizeof(bytes)/sizeof(int));
    int i = 0;
    int j = 0;
    int n = nr;

    while (n) {
        bytes[i] = n % 2;
        n = n / 2;
        i++;
    }

    printf("bin: ");
    for (j = i - 1; j >= 0; j--) {
        printf("%d", bytes[j]);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    if (argc == 1) {
        printf("usage: ./a.out <nr>\n");
        return -1;
    }
    const int nr = atoi(argv[1]);
    printf("decimal: %d\n", nr);
    decimalToBin(nr);
    return 0;
}