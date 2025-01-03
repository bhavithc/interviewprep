#include <iostream>

class Stack
{
public:
    // access
    int top();

    // capacity
    bool empty();
    int size();

    // modifiers
    void push(int);
    void pop();

    void printAll();
private:
    struct Node 
    {
        int item;
        Node* next;
    };

    Node* m_pRootNode {nullptr};
    uint64_t m_size {0};
};

int Stack::top()
{
    if (m_pRootNode == nullptr) {
        std::cerr << "No item found in stack!\n";
        return -1;
    }
    
    Node* pTmp = m_pRootNode;
    while (pTmp && pTmp->next) {
        pTmp = pTmp->next;
    }

    return pTmp->item;
}

bool Stack::empty()
{
    return m_pRootNode == nullptr;
}

int Stack::size()
{
    return m_size;
}

void Stack::printAll()
{
    if (m_pRootNode == nullptr) {
        return;
    }

    Node* pTmp = m_pRootNode;
    while (pTmp) {
        std::cout << pTmp->item << ", ";
        pTmp = pTmp->next;
    }

    std::cout << "\n";
}

void Stack::push(int item)
{
    Node* pNode = new Node;
    pNode->item = item;
    pNode->next = nullptr;

    if (m_pRootNode == nullptr) {
        m_size++;
        m_pRootNode = pNode;
        return;
    }

    Node* pTmp = m_pRootNode;
    while (pTmp && pTmp->next) {
        pTmp = pTmp->next;
    }
    m_size++;
    pTmp->next = pNode;
}

void Stack::pop()
{
    if (m_pRootNode == nullptr) {
        std::cerr << "Stack is empty unable to pop!\n";
        return;
    }

    Node* pTmp = m_pRootNode;
    Node* pLastButPrev = nullptr;

    while (pTmp && pTmp->next) {
        pLastButPrev = pTmp;
        pTmp = pTmp->next;
    }

    if (pLastButPrev) {
        pLastButPrev->next = nullptr;
        m_size--;
    } else {
        m_pRootNode = nullptr;
        m_size = 0;
    }

    std::cout << "Popping... " << pTmp->item << "\n";
    delete pTmp;
    pTmp = nullptr;
}

int main()
{
    Stack st;
    std::cout << "is empty ? " << std::boolalpha << st.empty() << "\n";
    st.push(1);
    st.push(2);
    st.push(90);
    st.printAll();
    std::cout << "is empty ? " << std::boolalpha << st.empty() << "\n";
    std::cout << "size : " << st.size() << "\n";
    std::cout << "top: " << st.top() << "\n";
    st.pop();
    st.pop();
    st.pop();
    st.pop();
    st.printAll();
    std::cout << "is empty ? " << std::boolalpha << st.empty() << "\n";
    std::cout << "size : " << st.size() << "\n";
    std::cout << "top: " << st.top() << "\n";
    


    

    return 0;
}

