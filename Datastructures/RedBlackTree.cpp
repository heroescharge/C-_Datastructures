#include <iostream>
#include <utility>

template <class K, class V>
class RedBlackTree {
private:
    struct Node {
        K key;
        V value;
        bool isRed; // If parent link is red

        Node *lChild;
        Node *rChild;
        Node *parent;

        Node(K key, V value, Node *parent, bool isRed) {
            this->key = key;
            this->value = value;
            this->isRed = isRed;
            this->parent = parent;

            lChild = nullptr;
            rChild = nullptr;
        }
    };

    struct Iterator {
        Node *node;
        Iterator(Node *node) {
            this->node = node;
        }

        std::pair<K, V> operator*() {
            return std::pair(node->key, node->value);
        }
        std::pair<K, V>* operator->() {
            return &(std::pair(node->key, node->value));
        }
        Iterator& operator++() {
            if (node->rChild == nullptr) {
                if (node->parent == nullptr) {
                    node = nullptr;
                }
                else {
                    while (node->parent != nullptr && node->parent->rChild == node) {
                        node = node->parent;
                    }
                    if (node->parent != nullptr) {
                        node = node->parent;
                    }
                    else {
                        node = nullptr;
                    }
                }
            }
            else {
                node = node->rChild;
                while (node->lChild != nullptr) {
                    node = node->lChild;
                }
            }
            return *this;
        }
        Iterator operator++(int) {
            Iterator it = *this;
            ++(*this);
            return it;
        }
        bool operator==(const Iterator other) const {
            return this->node == other.node;
        }
        bool operator!=(const Iterator other) const {
            return !(*this == other);
        }
    };

    Node *root;
    int numElements;

    void insert2(Node *parent, K key, V value) {
        if (key == parent->key) {
            parent->value = value;
        }
        else if (key < parent->key) {
            if (parent->lChild == nullptr) {
                parent->lChild = new Node(key, value, parent, true);
                numElements++;
                rebalanceTree(parent);
            }
            else {
                insert2(parent->lChild, key, value);
            }
        }
        else if (key > parent->key) {
            if (parent->rChild == nullptr) {
                parent->rChild = new Node(key, value, parent, true);
                numElements++;
                rebalanceTree(parent);
            }
            else {
                insert2(parent->rChild, key, value);
            }
        }
    }

    void rotateLeft(Node *node) {
        node->parent->rChild = node->lChild;
        node->lChild = node->parent;
        if(node->parent->parent != nullptr) {
            node->parent = node->lChild->parent;
            if (node->lChild->parent->rChild == node->lChild) {
                node->parent->rChild = node;
            }
            else {
                node->parent->lChild = node;
            }
        }
        else {
            node->parent = nullptr;
            root = node;
        }
        node->lChild->parent = node;

        node->isRed = node->lChild->isRed;
        node->lChild->isRed = true;
    }

    void rotateRight(Node *node) {
        node->parent->lChild = node->rChild;
        node->rChild = node->parent;
        if (node->parent->parent != nullptr) {
            node->parent = node->rChild->parent;
            if (node->parent->rChild == node->rChild) {
                node->parent->rChild = node;
            }
            else {
                node->parent->lChild = node;
            }
        }
        else {
            node->parent = nullptr;
            root = node;
        }
        node->rChild->parent = node;

        node->isRed = false;
        node->rChild->isRed = true;
    }

    void flipColor(Node *node) {
        node->isRed = true;
        node->lChild->isRed = false;
        node->rChild->isRed = false;
    }

    void rebalanceTree(Node *parent) {
        if (parent == nullptr) {
            return;
        }

        if (parent->lChild != nullptr && parent->rChild != nullptr && 
            parent->lChild->isRed && parent->rChild->isRed) 
        {
            flipColor(parent);
            rebalanceTree(parent->parent);
        }
        else if (parent->rChild != nullptr && parent->rChild->isRed) {
            rotateLeft(parent->rChild);
            rebalanceTree(parent->parent);
        }
        else if (parent->lChild != nullptr && parent->parent != nullptr && parent->isRed && parent->lChild->isRed) {
            rotateRight(parent);
            rebalanceTree(parent);
        }
    }

    void printTree2(Node *parent) {
        if (parent == nullptr) {
            return;
        }

        std::cout << "K: " << parent->key << " V: " << parent->value << std::endl;
        if (parent->parent == nullptr) {
            std::cout << "P: NULL" << std::endl;
        }
        else {
            std::cout << "P: " << parent->parent->key << " " 
                      << parent->parent->value <<  std::endl;
        }
        if (parent->isRed) {
            std::cout << "IS RED" << std::endl;
        }
        else {
            std::cout << "IS BLACK" << std::endl;
        }
        if (parent->lChild != nullptr) {
            std::cout << "LChild: " << parent->lChild->key << " " << parent->lChild->value << std::endl;
        }
        if (parent->rChild != nullptr) {
            std::cout << "RChild: " << parent->rChild->key << " " << parent->rChild->value << std::endl;
        }

        std::cout << std::endl;

        printTree2(parent->lChild);
        printTree2(parent->rChild);
    }

    void deleteMemory(Node *node) {
        if (node->lChild != nullptr) {
            deleteMemory(node->lChild);
        }
        if (node->rChild != nullptr) {
            deleteMemory(node->rChild);
        }
        delete node;
    }

public:
    RedBlackTree() {
        root = nullptr;
        numElements = 0;
    }

    ~RedBlackTree() {
        if (root != nullptr) {
            deleteMemory(root);
        }
    }

    int size() {
        return numElements;
    }

    bool isEmpty() {
        return size() == 0;
    }

    void insert(K key, V value) {
        if (root == nullptr) {
            root = new Node(key, value, nullptr, false);
            numElements++;
            return;
        }
        insert2(root, key, value);
        if (root->isRed) {
            root->isRed = false;
        }
    }

    V find(K key) {
        Node *currNode = root;
        while (currNode != nullptr) {
            if (key == currNode->key) {
                return currNode->value;
            }
            else if (key < currNode->key) {
                currNode = currNode->lChild;
            }
            else {
                currNode = currNode->rChild;
            }
        }

        return (V) NULL;
    }

    Iterator begin() {
        Node *smallestNode = root;
        if (smallestNode != nullptr) {
            while (smallestNode->lChild != nullptr) {
                smallestNode = smallestNode->lChild;
            }
        }
        return Iterator(smallestNode);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    // Prints the entire tree
    void printTree() {
        printTree2(root);
    }

};

int main() {
    RedBlackTree<int, int> tree;
    tree.insert(2, 3);
    tree.insert(1, 5);
    tree.insert(0, 1);
    tree.insert(4, 2);
    tree.insert(8, 3);
    tree.insert(6, -2);
    tree.insert(7, 8);

    tree.insert(7, 6);
    tree.insert(2, 6);

    std::cout << "Size: " << tree.size() << std::endl;
    std::cout << tree.find(1) << std::endl;
    std::cout << tree.find(2) << std::endl;
    std::cout << tree.find(0) << std::endl;
    std::cout << tree.find(4) << std::endl;
    std::cout << tree.find(6) << std::endl;
    std::cout << tree.find(7) << std::endl;
    std::cout << tree.find(8) << std::endl;

    std::cout << "Size: " << tree.size() << std::endl;

    for (std::pair<int, int> p : tree) {
        std::cout << p.first << " " << p.second << std::endl;
    }

    return 0;
}