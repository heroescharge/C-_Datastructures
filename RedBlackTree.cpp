#include <iostream>

template <class K, class V>
class RedBlackTree {
private:
    struct Node {
        K key;
        V value;
        bool isRed;

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

    };

    Node *root;
    int numElements;

    Node *insert2(Node *parent, K key, V value) {
        if (parent == nullptr) {
            return new Node(key, value, parent, true);
        }
        else if (key == parent->key) {
            parent->value = value;
        }
        else if (key < parent->key) {
            parent->lChild = insert2(parent->lChild, key, value);
        }
        else if (key > parent->key) {
            parent->rChild = insert2(parent->rChild, key, value);
        }
        rebalanceTree(parent);
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
        node->lChild->parent = node;
    }

    void rotateRight(Node *node) {
        node->parent->lChild = node->rChild;
        node->rChild = node->parent;
        if (node->parent->parent != nullptr) {
            node->parent = node->rChild->parent;
            if (node->rChild->parent->rChild == node->rChild) {
                node->parent->rChild = node;
            }
            else {
                node->parent->lChild = node;
            }
        }
        node->rChild->parent = node;
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

        if (parent->lChild->isRed && parent->rChild->isRed) {
            flipColor(parent);
            rebalanceTree(parent->parent);
        }
        else if (parent->rChild->isRed) {
            rotateLeft(parent->rChild);
            rebalanceTree(parent->parent);
        }
        else if (parent->isRed && parent->lChild->isRed) {
            rotateRight(parent);
            rebalanceTree(parent);
        }
    }

public:
    RedBlackTree() {
        root = nullptr;
        numElements = 0;
    }

    ~RedBlackTree() {

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
        }
        else if (key == root->key) {
            root->value = value;
        }
        else if (key < root->key) {
            root->lChild = insert2(root->lChild, key, value);
        }
        else if (key > root->key) {
            root->rChild = insert2(root->rChild, key, value);
        }
    }

    V find(K key) {
        Node *currNode = root;
        while (currNode != null) {
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

        return nullptr;
    }

    void remove(K key) {

    }

    Iterator begin() {

    }

    Iterator end() {
    }

};

int main() {

    return 0;
}