#include <iostream>
#include <stdexcept>

template <class T>
class Queue {
private:
    struct Node {
        T value;
        Node *next;

        Node(T value, Node *next) {
            this->value = value;
            this->next = next;
        }
    };

    Node *firstNode;
    Node *lastNode;
    int numElements;

    struct Iterator {
    private:
        Node *node;
    public:
        Iterator(Node *node) {
            this->node = node;
        }
        T operator*() {
            return node->value;
        }
        T* operator->() {
            return &(node->value);
        }
        Iterator& operator++() {
            this->node = this->node->next;
            return *this;
        }
        Iterator operator++(int) {
            Iterator itCopy = *this;
            this->node = this->node->next;
            return itCopy;
        }
        bool operator==(const Iterator other) const {
            return node == other.node;
        }
        bool operator!=(const Iterator other) const {
            return node != other.node;
        }
    };

public:
    Queue() {
        numElements = 0;
        firstNode = nullptr;
        lastNode = nullptr;
    }

    ~Queue() {
        while (firstNode != nullptr) {
            Node *firstNodeCopy = firstNode;
            firstNode = firstNode->next;
            delete firstNodeCopy;
        }
    }

    bool isEmpty() {
        return numElements == 0;
    }

    int size() {
        return numElements;
    }

    void enqueue(T value) {
        Node *newNode = new Node(value, nullptr);
        if (lastNode != nullptr) {
            lastNode->next = newNode;
        }
        if (isEmpty()) {
            firstNode = newNode;
        }
        lastNode = newNode;

        numElements++;
    }

    T pop() {
        if (firstNode == nullptr) { throw std::underflow_error("No elements in queue"); }

        Node *firstNodeCopy = firstNode;
        T item = firstNode->value;

        firstNode = firstNode->next;
        delete firstNodeCopy;

        numElements--;

        if (isEmpty()) {
            lastNode = nullptr;
        }

        return item;
    }

    T peek() {
        if (firstNode == nullptr) { throw std::underflow_error("No elements in queue"); }

        return firstNode->value;
    }

    Iterator begin() {
        return Iterator(firstNode);
    }

    Iterator end() {
        return Iterator(nullptr);
    }  
};

int main() {
    Queue<int> q;

    q.enqueue(2);
    q.enqueue(1);
    q.enqueue(4);
    q.enqueue(-3);
    q.enqueue(-6);

    std::cout << "Size: " << q.size() << std::endl;
    while (!q.isEmpty()) {
        std::cout << q.peek() << std::endl;
        std::cout << q.pop() << std::endl;
    }

    q.enqueue(2);
    q.enqueue(1);
    q.enqueue(4);
    q.enqueue(-3);
    for (int x : q) {
        std::cout << x << std::endl;
        q.pop();
    }

    return 0;
}