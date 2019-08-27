#include <vector>
using namespace std;

#include "test_runner.h"

template <typename T>
class LinkedList {
public:
    struct Node {
        T value;
        Node *next = nullptr;
    };

    ~LinkedList()
    {
        while (head != nullptr) {
            PopFront();
        }
    }

    void PushFront(const T &value)
    {
        Node *node = new Node{value, head};
        head = node;
    }

    void InsertAfter(Node *node, const T &value)
    {
        if (node == nullptr) {
            PushFront(value);
            return;
        }

        Node *next_node = new Node{value, node->next};
        node->next = next_node;
    }

    void PopFront()
    {
        if (head == nullptr) {
            return;
        }

        Node *prev_head = head;
        head = head->next;
        delete prev_head;
    }

    void RemoveAfter(Node *node)
    {
        if (node == nullptr) {
            PopFront();
            return;
        }
        else if (node->next == nullptr) {
            return;
        }

        Node *old_node = node->next;
        node->next = node->next->next;
        delete old_node;
    }

    Node *GetHead() { return head; }
    const Node *GetHead() const { return head; }

private:
    Node *head = nullptr;
};