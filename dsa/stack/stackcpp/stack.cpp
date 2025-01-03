#include <iostream>
#include <stack>

int main()
{
    std::stack<int> st;
    for (int i = 0; i < 10; i++) {
        st.push(i);
    }

    std::cout << "size: " << st.size() << "\n";
    std::cout << "top: " << st.top() << "\n";
    std::cout << "is empty? " << std::boolalpha <<  st.empty() << "\n";
    for (int i = 0; i < 10; i++) {
        std::cout << st.top() << "\n";
        st.pop();

        std::cout << "- size: " << st.size() << "\n";
        std::cout << "- top: " << (!st.empty() ? st.top() : -1) << "\n";
        std::cout << "- is empty? " << std::boolalpha <<  st.empty() << "\n\n";
    }

    return 0;
}