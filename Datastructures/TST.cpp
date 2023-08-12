#include <iostream>
#include <string>
#include <format>

template <class V>
class TST {
private:
    static const int CHAR_SIZE = 256;

    class Node {
    public:
        bool isValue;
        char c;
        V value;
        Node *children[3];
        Node *parent;
        int numChildren = 0;

        Node(Node *parent, char c) {
            this->c = c;
            this->parent = parent;
            isValue = false;
            for (int i = 0; i < 3; i++) {
                children[i] = nullptr;
            }
        }
        
        Node(int value, Node *parent, char c) {
            this->c = c;
            this->parent = parent;
            isValue = true;
            this->value = value;
            for (int i = 0; i < 3; i++) {
                children[i] = nullptr;
            }
        }
    };

    Node *root;

    void deleteNode(Node *node, bool isBottomNode) {
        if (isBottomNode) {
            node->isValue = false;
        }
        if (node->numChildren == 0 && !node->isValue) {
            node->parent->numChildren--;
            Node *parentNode = node->parent;
            for (int i = 0; i < 3; i++) {
                if ((parentNode->children)[i] == node) {
                    (parentNode->children)[i] = nullptr;
                }
            }
            delete node;
            deleteNode(parentNode, false);
        }
    }

    void deleteNodeMemory(Node *node) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < 3; i++) {
            deleteNodeMemory((node->children)[i]);
        }
        delete node;
    }

    void searchStrings(Node *node, std::string prefixStr, std::vector<std::string> &keyList) {
        if (node == nullptr) {
            return;
        }
        std::string newStr = prefixStr + node->c;
        if (node->isValue) {
            keyList.push_back(newStr);
        }
        searchStrings((node->children)[0], prefixStr, keyList);
        searchStrings((node->children)[1], newStr, keyList);
        searchStrings((node->children)[2], prefixStr, keyList);
    }

public:
    TST() {
        root = nullptr;
    }

    ~TST() {
        deleteNodeMemory(root);
    }

    bool contains(std::string str) {
        Node *currNode = root;
        for (int i = 0; i < str.size() - 1; i++) {
            while (currNode != nullptr && currNode->c != str[i]) {
                if (str[i] < currNode->c) {
                    currNode = (currNode->children)[0];
                }
                else {
                    currNode = (currNode->children)[2];
                }
            }
            if (currNode == nullptr) {
                return false;
            }

            currNode = (currNode->children)[1];
        }

        if (currNode == nullptr || currNode->c != str[str.length() - 1]) {
            return false;
        }

        return true;
    }

    V get(std::string str) {
        Node *currNode = root;
        for (int i = 0; i < str.size() - 1; i++) {
            while (currNode != nullptr && currNode->c != str[i]) {
                if (str[i] < currNode->c) {
                    currNode = (currNode->children)[0];
                }
                else {
                    currNode = (currNode->children)[2];
                }
            }
            if (currNode == nullptr) {
                return false;
            }

            currNode = (currNode->children)[1];
        }

        if (currNode == nullptr || currNode->c != str[str.length() - 1]) {
            throw std::invalid_argument("Doesn't contain {}" + str);
        }

        return currNode->value;
    }

    void put(std::string str, V value) {
        if (str.length() == 0) { throw std::invalid_argument("String can't have length 0"); }
        if (root == nullptr) {
            root = new Node(nullptr, str[0]);
        }
        Node *currNode = root;
        for (int i = 0; i < str.size() - 1;) {
            int childIndex;
            if (str[i] < currNode->c) {
                childIndex = 0;
            }
            else if (str[i] == currNode->c) {
                childIndex = 1;
                i++;
            }
            else {
                childIndex = 2;
            }

            if ((currNode->children)[childIndex] == nullptr) {
                (currNode->children)[childIndex] = new Node(currNode, str[i]);
                currNode->numChildren++;
            }

            currNode = (currNode->children)[childIndex];
        }

        currNode->isValue = true;
        currNode->value = value;
    }

    void remove(std::string str) {
        Node *currNode = root;
        for (int i = 0; i < str.size() - 1; i++) {
            while (currNode != nullptr && currNode->c != str[i]) {
                if (str[i] < currNode->c) {
                    currNode = (currNode->children)[0];
                }
                else {
                    currNode = (currNode->children)[2];
                }
            }
            if (currNode == nullptr) {
                throw std::invalid_argument("Doesn't contain {}" + str);
            }

            currNode = (currNode->children)[1];
        }

        if (currNode == nullptr || currNode->c != str[str.length() - 1]) {
            throw std::invalid_argument("Doesn't contain {}" + str);
        }

        deleteNode(currNode, true);
    }

    std::vector<std::string> keys() {
        std::vector<std::string> keyList = std::vector<std::string>();

        searchStrings(root, "", keyList);

        return keyList;
    }
};

int main() {
    TST<int> trie = TST<int>();
    trie.put("abc", 2);
    trie.put("abc", 4);
    trie.put("hello_world", 5);
    trie.put("hello_wo", 3);
    trie.put("hello_woke", 9);
    for (std::string s : trie.keys()) {
        std::cout << s << std::endl;
    }
    std::cout << trie.contains("") << std::endl;
    std::cout << trie.contains("hello_w") << std::endl;
    std::cout << trie.contains("abc") << std::endl;
    std::cout << trie.get("abc") << std::endl;

    trie.remove("hello_world");
    std::cout << trie.get("hello_wo") << std::endl;
    std::cout << trie.get("hello_woke") << std::endl;

    trie.remove("hello_woke");
    std::cout << trie.get("hello_wo") << std::endl;

    return 0;
}