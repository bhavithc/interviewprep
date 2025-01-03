#include <iostream>
#include <queue>
#include <cassert>

int main()
{
    std::queue<int> q;
    q.push(0); // 0
    q.push(1); // 0 1
    q.push(2); // 0 1 2
    q.push(3); // 0 1 2 3
    
    assert(q.empty() == false);
    assert(q.front() == 0);
    assert(q.back() == 3);

    std::cout << "q: ";
    for (;!q.empty();q.pop()) {
        std::cout << q.front() << " " << std::flush;
    }
    std::cout << "\n";
    assert(q.empty() == true);

    return 0;
}