#include <iostream>

template <class K, class V>
class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node *next;

        Node(K key, V value) {
            this->key = key;
            this->value = value;
            next = nullptr;
        }
    };

    struct Iterator {
        Node **table;
        Node *currNode;
        int index;
        int MAX_SIZE;

        Iterator(Node **table, int index, int MAX_SIZE) {
            this->table = table;
            this->index = index;
            this->MAX_SIZE = MAX_SIZE;
            if (index >= MAX_SIZE) {
                currNode = nullptr;
            }
            else {
                currNode = table[index];
            }
        }

        K operator*() {
            return currNode->key;
        }

        K* operator->(){
            return &(currNode->key);
        }

        Iterator& operator++() {
            currNode = currNode->next;
            if (currNode == nullptr) {
                do {
                    index++;
                } while (index < MAX_SIZE && table[index] == nullptr);
                if (index < MAX_SIZE) {
                    currNode = table[index];
                }
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator it = *this;
            ++(*this);

            return it;
        }

        bool operator==(Iterator other) {
            return other.currNode == currNode;
        }

        bool operator!=(Iterator other) {
            return other.currNode != currNode;
        }
    };

    int MAX_SIZE;
    int numElements;
    Node **table;

public:
    HashMap(int MAX_SIZE) {
        numElements = 0;
        this->MAX_SIZE = MAX_SIZE;
        table = new Node*[MAX_SIZE];

        for (int i = 0; i < MAX_SIZE; i++) { table[i] = nullptr; }
    }

    ~HashMap() {
        Node *currNode;
        Node *nextNode;
        for (int i = 0; i < MAX_SIZE; i++) {
            currNode = table[i];
            while (currNode != nullptr) {
                nextNode = currNode->next;
                delete currNode;
                currNode = nextNode;
            }
        }
        delete[] table;
    }

    int size() {
        return numElements;
    }

    bool isEmpty() {
        return numElements == 0;
    }

    bool contains(K key) {
        Node *currNode = table[key % MAX_SIZE];
        while (currNode != nullptr) {
            if (currNode->key == key) {
                return true;
            }
            currNode = currNode->next;
        }

        return false;
    }

    void put(K key, V value) {
        Node *currNode = table[key % MAX_SIZE];
        if (currNode == nullptr) {
            table[key % MAX_SIZE] = new Node(key, value);
            numElements++;
            return;
        }

        Node *prevNode;
        while (currNode != nullptr) {
            if (currNode->key == key) {
                currNode->value = value;
                return;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }

        prevNode->next = new Node(key, value);
        numElements++;
    }

    void remove(K key) {
        Node *currNode = table[key % MAX_SIZE];
        Node *prevNode = nullptr;

        while (currNode != nullptr) {
            if (currNode->key == key) {
                if (prevNode != nullptr) {
                    prevNode->next = currNode->next;
                }
                else {
                    table[key % MAX_SIZE] = nullptr;
                }
                delete currNode;
                numElements--;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
    }

    V get(K key) {
        Node *currNode = table[key % MAX_SIZE];
        while (currNode != nullptr) {
            if (currNode->key == key) {
                return currNode->value;
            }
            currNode = currNode->next;
        }

        return (V) NULL;
    }

    Iterator begin() {
        int i = 0;
        while (i < MAX_SIZE && table[i] == nullptr) {
            i++;
        }
        return Iterator(table, i, MAX_SIZE);
    }

    Iterator end() {
        return Iterator(table, MAX_SIZE, MAX_SIZE);
    }

};

int main() {
    HashMap<int, char> map(10);
    map.put(2, 'a');
    map.put(4, 'b');
    map.put(12, 'c');
    map.put(3, 'd');
    map.put(19, 'e');
    map.put(12, 'f');

    std::cout << "Size: " << map.size() << std::endl;
    std::cout << map.get(2) << std::endl;
    std::cout << map.get(4) << std::endl;
    std::cout << map.get(12) << std::endl;
    std::cout << map.get(3) << std::endl;
    std::cout << map.get(19) << std::endl;
    std::cout << (map.get(-4) == (char) NULL)<< std::endl;

    std::cout << "Iteration start" << std::endl;
    for (int key : map) {
        std::cout << key << std::endl;
    }
    std::cout << "Iteration end" << std::endl;

    map.remove(99);
    map.remove(12);
    map.remove(2);

    std::cout << "Size: " << map.size() << std::endl;
    std::cout << map.get(4) << std::endl;
    std::cout << map.get(3) << std::endl;
    std::cout << map.get(19) << std::endl;

    return 0;
}