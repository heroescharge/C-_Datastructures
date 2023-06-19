#include <iostream>
#include <stdexcept>

class UnionFind{
private:
    int n;
    int numComponents;
    int *id; // Tracks parent id of nodes
    int *size; // Tracks size of subtree of node

    // Get root of node p
    int root(int p) {
        if (p < 0 || p >= n) { throw std::invalid_argument("Node is not in datastructure"); }

        while (id[p] != p) {
            p = id[p];
            id[p] = id[id[p]];
        }

        return p;
    }

public:
    UnionFind(int n) {
        this->n = n;

        id = new int[n];
        for (int i = 0; i < n; i++) {
            id[i] = i;
        }

        size = new int[n];
        for (int i = 0; i < n; i++) {
            size[i] = 1;
        }

        numComponents = n;
    }

    ~UnionFind() {
        delete[] id;
        delete[] size;
    }

    // Draw connection between nodes p and q
    void unify(int p, int q) {
        if (p < 0 || p >= n) { throw std::invalid_argument("Node is not in datastructure"); }
        if (q < 0 || q >= n) { throw std::invalid_argument("Node is not in datastructure"); }

        int pRoot = root(p);
        int qRoot = root(q);

        if (pRoot == qRoot) {
            return;
        }
        
        if (size[pRoot] <= size[qRoot]) {
            id[pRoot] = id[qRoot];
            size[qRoot] += size[pRoot];
        }
        else {
            id[qRoot] = id[pRoot];
            size[pRoot] += size[qRoot];
        }

        numComponents--;
    }

    // Check if nodes p and q are connected
    bool connected(int p, int q) {
        if (p < 0 || p >= n) { throw std::invalid_argument("Node is not in datastructure"); }
        if (q < 0 || q >= n) { throw std::invalid_argument("Node is not in datastructure"); }

        return root(p) == root(q);
    }

    // Return number of connected components
    int count() {
        return numComponents;
    }
};

// Test client
int main() {
    const int SIZE = 6;
    UnionFind uf(SIZE);

    std::cout << "Initial state:" << std::endl;
    std::cout << uf.count() << std::endl;

    uf.unify(0, 1);
    uf.unify(2, 3);
    uf.unify(2, 5);
    uf.unify(4, 4);
    uf.unify(3, 5);

    std::cout << "Unified state:" << std::endl;
    std::cout << uf.count() << std::endl;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << i << " connected to " << j 
            << "?: " << uf.connected(i, j) << std::endl;
        }
    }

    return 0;
}

