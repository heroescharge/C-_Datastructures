#include <iostream>
#include <string>
#include <format>

template <class V>
class RWayTrie {
private:
    static const int CHAR_SIZE = 256;

    class Node {
    public:
        bool isValue;
        char c;
        V value;
        Node *children[CHAR_SIZE];
        Node *parent;
        int numChildren = 0;

        Node(Node *parent, char c) {
            this->c = c;
            this->parent = parent;
            isValue = false;
            for (int i = 0; i < CHAR_SIZE; i++) {
                children[i] = nullptr;
            }
        }
        
        Node(int value, Node *parent, char c) {
            this->c = c;
            this->parent = parent;
            isValue = true;
            this->value = value;
            for (int i = 0; i < CHAR_SIZE; i++) {
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
            parentNode->children[node->c] = nullptr;
            delete node;
            deleteNode(parentNode, false);
        }
    }

    void deleteNodeMemory(Node *node) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < CHAR_SIZE; i++) {
            deleteNodeMemory((node->children)[i]);
        }
        delete node;
    }

    void searchStrings(Node *node, std::string prefixStr, std::vector<std::string> &keyList) {
        for (int i = 0; i < CHAR_SIZE; i++) {
            std::string newPrefixString = prefixStr + (char) i;
            if (node->children[i] != nullptr) {
                if ((node->children[i])->isValue) {
                    keyList.push_back(newPrefixString);
                }
                searchStrings(node->children[i], newPrefixString, keyList);
            }
        }
    }

public:
    RWayTrie() {
        root = new Node(nullptr, '\0');
    }

    ~RWayTrie() {
        deleteNodeMemory(root);
    }

    bool contains(std::string str) {
        Node *currNode = root;
        for (int i = 0; i < str.size(); i++) {
            if ((currNode->children)[str[i]] == nullptr) {
                return false;
            }

            currNode = (currNode->children)[str[i]];
        }

        return currNode->isValue;
    }

    V get(std::string str) {
        Node *currNode = root;
        for (int i = 0; i < str.size(); i++) {
            if ((currNode->children)[str[i]] == nullptr) {
                throw std::invalid_argument("Doesn't contain {}" + str);
            }

            currNode = (currNode->children)[str[i]];
        }

        if (!currNode->isValue) {
            throw std::invalid_argument("Doesn't contain {}" + str);
        }

        return currNode->value;
    }

    void put(std::string str, V value) {
        Node *currNode = root;
        for (int i = 0; i < str.size(); i++) {
            if ((currNode->children)[str[i]] == nullptr) {
                (currNode->children)[str[i]] = new Node(currNode, str[i]);
                currNode->numChildren++;
            }

            currNode = (currNode->children)[str[i]];
        }

        currNode->isValue = true;
        currNode->value = value;
    }

    void remove(std::string str) {
        Node *currNode = root;
        for (int i = 0; i < str.size(); i++) {
            if ((currNode->children)[str[i]] == nullptr) {
                throw std::invalid_argument("Doesn't contain {}" + str);
            }

            currNode = (currNode->children)[str[i]];
        }
        if (!currNode->isValue) {
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
    RWayTrie<int> trie = RWayTrie<int>();
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
}