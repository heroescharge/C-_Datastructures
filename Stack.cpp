#include <iostream>
#include <stdexcept>

template <class T>
class Stack {
private:
    struct Node {
        T value;
        Node *next;

        Node(T value, Node *next) {
            this->value = value;
            this->next = next;
        }
    };

    int numElements;
    Node *topNode;

    struct Iterator {
        Node *node;

        Iterator(Node *node) {
            this->node = node;
        }

        T operator*() const {
            return node->value;
        }

        T* operator->() const {
            return &(node->value);
        }

        bool operator==(const Iterator other) const {
            return node == other.node;
        }

        bool operator!=(const Iterator other) const {
            return node != other.node;
        }

        Iterator& operator++() {
            this->node = this->node->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator itCopy = *this;
            ++(*this);
            return itCopy;
        }
    };

public:
    Stack() {
        numElements = 0;
        topNode = nullptr;
    }

    ~Stack() {
        while (topNode != nullptr) {
            Node *currNode = topNode;
            topNode = topNode->next;
            delete currNode;
        }
    }

    bool isEmpty() {
        return numElements == 0;
    }

    int size() {
        return numElements;
    }

    void push(T item) {
        Node *newNode = new Node(item, nullptr);
        newNode->next = topNode;
        topNode = newNode;

        numElements++;
    }

    T peek() {
        if (topNode == nullptr) { throw std::underflow_error("No elements in stack"); }

        return topNode->value;
    }

    T pop() {
        if (topNode == nullptr) { throw std::underflow_error("No elements in stack"); }

        Node *topNodeCopy = topNode;
        T item = topNode->value;

        topNode = topNode->next;

        delete topNodeCopy;

        numElements--;
        return item;
    }

    Iterator begin() {
        return Iterator(topNode);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};


// Test client
int main() {
    Stack<int> stack;

    stack.push(2);
    stack.push(1);
    stack.push(4);
    stack.push(-3);
    stack.push(-6);

    std::cout << "Size: " << stack.size() << std::endl;
    while (!stack.isEmpty()) {
        std::cout << stack.peek() << std::endl;
        std::cout << stack.pop() << std::endl;
    }

    stack.push(2);
    stack.push(1);
    stack.push(4);
    stack.push(-3);
    for (int x : stack) {
        std::cout << x << std::endl;
        stack.pop();
    }

    return 0;
}