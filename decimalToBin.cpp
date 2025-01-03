#include <iostream>
#include <bitset>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc == 1) {
        std::cerr << "Invalid arg: \n";
        std::cerr << "Usage: ./a.out <nr>\n";
        return 0;
    }

    const long long unsigned int nr = atoi(argv[1]);
    std::bitset<32> binary {nr};

    std::cout << "decimal: " << nr << "\n";
    std::cout << "bin: " << binary << "\n";
    return 0;
}