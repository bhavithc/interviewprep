#include <iostream>
#include <exception>
#include <mutex>
#include <atomic>
#include <cassert>

class Queue
{
public:
    void push(int);
    void pop();
    int front();
    int back();
    int size();
    bool empty();
private:
    struct Node 
    {
        int item;
        Node* next;
    };

    Node* m_pRootNode {nullptr};
    std::atomic_int m_size {0};
    std::mutex m_mtx;
    
};

void Queue::push(int item)
{
    std::lock_guard<std::mutex> lock {m_mtx};

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

void Queue::pop()
{
    std::lock_guard<std::mutex> lock {m_mtx};

    // if no element
    if (m_pRootNode == nullptr) {
        return;
    }

    // if one element
    if (m_pRootNode->next == nullptr) {
        delete m_pRootNode;
        m_pRootNode = nullptr;
        m_size = 0;
        return;
    }

    // if more than one element 
    Node* pTmp = m_pRootNode;
    m_pRootNode = pTmp->next;
    delete pTmp;
    m_size--;
}

int Queue::front()
{
    std::lock_guard<std::mutex> lock {m_mtx};
    if (m_pRootNode == nullptr) {
        throw std::runtime_error("No item found in queue!");
    }

    return m_pRootNode->item;
}

int Queue::back()
{
    std::lock_guard<std::mutex> lock {m_mtx};
    if (m_pRootNode == nullptr) {
        throw std::runtime_error("No item found in queue!");
    }

    Node* pTmp = m_pRootNode;
    while (pTmp && pTmp->next) {
        pTmp = pTmp->next;
    }

    return pTmp->item;
}

int Queue::size()
{
    return m_size;
}

bool Queue::empty()
{
    return m_size == 0;
}


int main()
{
    Queue q;
    q.push(0); // back pushes 0
    q.push(1); // q = 0 1
    q.push(2); // q = 0 1 2
    q.push(3); // q = 0 1 2 3
 
    assert(q.front() == 0);
    assert(q.back() == 3);
    assert(q.size() == 4);
 
    q.pop(); // removes the front element, 0
    assert(q.size() == 3);
 
    // // Print and remove all elements. Note that std::queue does not
    // // support begin()/end(), so a range-for-loop cannot be used.
    std::cout << "q: ";
    for (; !q.empty(); q.pop()) 
        std::cout << q.front() << ' ' << std::flush;
    std::cout << '\n';
    assert(q.size() == 0);
}