#include <iostream>

class LinkedList
{
public:
    void insertRear(int item);
    void insertFront(int item);
    void deleteRear();
    void deleteFront();
    void printAll();
private:
    struct Node 
    {
        int item;
        Node* next;
    };

    Node* m_pRootNode {nullptr};
};

void LinkedList::insertRear(int item)
{
    Node* pNode = new Node;
    pNode->item = item;
    pNode->next = nullptr;

    // if no item present
    if (m_pRootNode == nullptr) {
        m_pRootNode = pNode;
        return;
    }

    // if one item present
    if (m_pRootNode->next == nullptr) {
        m_pRootNode->next = pNode;
        return;
    }
    
    // if more than one item present
    Node* pTmp = m_pRootNode;
    while (pTmp && pTmp->next) {
        pTmp = pTmp->next;
    }
    
    pTmp->next = pNode;
}

void LinkedList::insertFront(int item)
{
    Node* pNode = new Node;
    pNode->item = item;
    pNode->next = nullptr;

    // if no item found 
    if (m_pRootNode == nullptr) {
        m_pRootNode = pNode;
        return;
    }

    // if 1 or more item present
    Node* pTmp = m_pRootNode;
    m_pRootNode = pNode;
    m_pRootNode->next = pTmp;
}

void LinkedList::deleteRear()
{
    // if no item present
    if (m_pRootNode == nullptr) {
        return;
    }

    // if one item present
    if (m_pRootNode->next == nullptr) {
        delete m_pRootNode;
        m_pRootNode = nullptr;
        return;
    }

    // if more than one node is present 
    Node* pTmp = m_pRootNode;
    Node* pLastButPrev = m_pRootNode;
    while (pTmp && pTmp->next) {
        pLastButPrev = pTmp;
        pTmp = pTmp->next;
    }

    delete pTmp;
    if (pLastButPrev) {
        pLastButPrev->next = nullptr;
    }
}

void LinkedList::deleteFront()
{
    // if no element 
    if (m_pRootNode == nullptr) {
        return;
    }

    // if one item present
    if (m_pRootNode->next == nullptr) {
        delete m_pRootNode;
        m_pRootNode = nullptr;
        return;
    }

    // if more than one item present
    Node* pTmp = m_pRootNode;
    m_pRootNode = pTmp->next;
    delete pTmp;
}

void LinkedList::printAll()
{
    if (m_pRootNode == nullptr) {
        std::cerr << "List is empty, nothing to print \n";
        return;
    }

    Node* pTmp = m_pRootNode;
    while (pTmp) {
        std::cout << pTmp->item << "->";
        pTmp = pTmp->next;
    }

    std::cout << "null" << std::endl;
}

int main()
{
    LinkedList list;
    list.printAll();

    list.insertFront(0); // 0
    list.insertFront(1); // 1, 0
    list.printAll();
    list.insertRear(2); // 1, 0, 2
    list.insertRear(3); // 1, 0, 2, 3
    list.printAll();
    list.deleteRear(); // 1, 0, 2
    list.printAll();
    list.deleteFront(); // 0, 2
    list.printAll();
    list.deleteFront(); // 2
    list.printAll();
    list.deleteFront(); // 
    list.printAll();
    list.deleteRear();
    list.printAll();

    return 0;
}

