#include <iostream>
#include <vector>
#include <utility>

// Copy pasted from Datastructures/UnionFind.cpp
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

template <class K>

class IndexedPQ {
public:
    int N;
    K *keys;
    int *heapIndex;
    std::vector<int> heap;

    void sink(int i) {
        while (2 * i <= heap.size() - 1) {
            if (2 * i + 1 <= heap.size() - 1 && keys[heap[2 * i + 1]] < keys[heap[2 * i]]) {
                if (keys[heap[i]] > keys[heap[2 * i + 1]]) {
                    std::swap(heap[i], heap[2 * i + 1]);
                    std::swap(heapIndex[heap[i]], heapIndex[heap[2 * i + 1]]);
                    i = 2 * i + 1;
                }
                else {
                    break;
                }
            }
            else {
                if (keys[heap[i]] > keys[heap[2 * i]]) {
                    std::swap(heap[i], heap[2 * i]);
                    std::swap(heapIndex[heap[i]], heapIndex[heap[2 * i]]);
                    i = 2 * i;
                }
                else {
                    break;
                }
            }
        }
    }

    void swim(int i) {
        while (i / 2 >= 1) {
            if (keys[heap[i]] < keys[heap[i / 2]]) {
                std::swap(heap[i], heap[i / 2]);
                std::swap(heapIndex[heap[i]], heapIndex[heap[i / 2]]);
                i /= 2;
            }
            else {
                break;
            }
        }
    }

public:
    IndexedPQ(int N) {
        this->N = N;
        keys = new K[N];
        heapIndex = new int[N];
        for (int i = 0; i < N; i++) {
            heapIndex[i] = -1;
        }
        heap.push_back(-1); // First element is null; start at index 1
    }

    ~IndexedPQ() {
        delete[] keys;
        delete[] heapIndex;
    }

    int size() {
        return heap.size() - 1;
    }

    bool isEmpty() {
        return size() == 0;
    }

    bool contains(int index) {
        return heapIndex[index] != -1;
    }

    void insert(int index, K key) {
        if (index < 0 || index >= N) {
            throw std::invalid_argument("Index out of range");
        }
        if (heapIndex[index] != -1) {
            throw std::invalid_argument("Index is already in priority queue");
        }


        heap.push_back(index);
        keys[index] = key;
        heapIndex[index] = heap.size() - 1;
        swim(heap.size() - 1);
    }

    void changeKey(int index, K key) {
        if (index < 0 || index >= N) {
            throw std::invalid_argument("Index out of range");
        }
        if (heapIndex[index] == -1) {
            throw std::invalid_argument("Index is not in priority queue");
        }

        keys[index] = key;
        swim(heapIndex[index]);
        sink(heapIndex[index]);
    }

    int pop() {
        if (isEmpty()) { throw std::underflow_error("Heap is empty"); }

        int value = heap[1];
        std::swap(heap[1], heap[heap.size() - 1]);
        std::swap(heapIndex[heap[1]], heapIndex[heap[heap.size() - 1]]);

        heap.erase(heap.begin() + (heap.size() - 1));
        heapIndex[value] = -1;
        sink(1);

        return value;
    }

    int peek() {
        if (isEmpty()) { throw std::underflow_error("Heap is empty"); }

        return heap[1];
    }

    void remove(int index) {
        if (isEmpty()) { throw std::underflow_error("Heap is empty"); }
        if (index < 0 || index >= N) {
            throw std::invalid_argument("Index out of range");
        }

        std::swap(heap[heapIndex[index]], heap[heap.size() - 1]);
        std::swap(heapIndex[index], heapIndex[heap[heapIndex[index]]]);


        heap.erase(heap.begin() + (heap.size() - 1));
        heapIndex[index] = -1;
        sink(1);
    }

    K getKey(int index) {
        if (index < 0 || index >= N) {
            throw std::invalid_argument("Index out of range");
        }
        if (heapIndex[index] == -1) {
            throw std::invalid_argument("Index not in heap");
        }

        return keys[index];
    }

    void print() {
        for (int i = 1; i < heap.size(); i++) {
            std::cout << heap[i] << " ";
        }
    }
};

struct Edge {
    // Undirected edge from u to v with weight w
    int u;
    int v;
    int w;

    Edge() {
        this->u = -1;
        this->v = -1;
        this->w = -1;
    }

    Edge(int u, int v, int w) {
        this->u = u;
        this->v = v;
        this->w = w;
    }

    bool operator>(const Edge other) const {
        return this->w > other.w;
    }
    bool operator<(const Edge other) const {
        return !(*this > other);
    }
    bool operator==(const Edge other) const {
        return this->w == other.w;
    }
    bool operator!=(const Edge other) const {
        return !(*this == other);
    }
};

std::vector<Edge> kruskals(std::vector<Edge> edges) {
    // Get vertex count (assuming connected graph)
    int V = 0;
    for (Edge e : edges) {
        V = std::max(std::max(V, e.u), e.v);
    }
    V++;

    std::vector<Edge> mstEdges = std::vector<Edge>();
    std::sort(edges.begin(), edges.end());
    UnionFind uf = UnionFind(V);

    for (Edge e : edges) {
        if (!uf.connected(e.u, e.v)) {
            mstEdges.push_back(e);
            uf.unify(e.u, e.v);
        }
    }

    return mstEdges;
}


std::vector<Edge> prims(std::vector<Edge> edges) {
    // Get vertex count (assuming connected graph)
    int V = 0;
    for (Edge e : edges) {
        V = std::max(std::max(V, e.u), e.v);
    }
    V++;

    // Get adj list representation
    std::vector<std::vector<Edge>> adjList = std::vector<std::vector<Edge>>(V);
    for (Edge e : edges) {
        adjList[e.u].push_back(e);
        adjList[e.v].push_back(e);
    }

    // Begin prims
    std::vector<Edge> mstEdges = std::vector<Edge>();

    bool visited[V];
    for (int i = 0; i < V; i++) { visited[i] = false; }
    IndexedPQ<Edge> vertexPQ = IndexedPQ<Edge>(V);

    visited[0] = true;
    int treeSize = 1;
    for (Edge e : adjList[0]) {
        vertexPQ.insert(e.u != 0 ? e.u : e.v, e);
    }
    while (treeSize < V) {
        int nextVertex = vertexPQ.peek();
        mstEdges.push_back(vertexPQ.getKey(nextVertex));
        visited[nextVertex] = true;
        vertexPQ.remove(nextVertex);

        for (Edge e : adjList[nextVertex]) {
            int otherVertex = e.u != nextVertex ? e.u : e.v;
            if (!visited[otherVertex]) {
                if (vertexPQ.contains(otherVertex)) {
                    if (vertexPQ.getKey(otherVertex) > e) {
                        vertexPQ.changeKey(otherVertex, e);
                    }
                }
                else {
                    vertexPQ.insert(otherVertex, e);
                }
            }
        }
        treeSize++;
    }

    return mstEdges;
}

int main() {
    std::vector<Edge> graph = std::vector<Edge> {
        Edge(4, 5, 35),
        Edge(4, 7, 37),
        Edge(5, 7, 28),
        Edge(0, 7, 16),
        Edge(1, 5, 32),
        Edge(0, 4, 38),
        Edge(2, 3, 17),
        Edge(1, 7, 19),
        Edge(0, 2, 26),
        Edge(1, 2, 36),
        Edge(1, 3, 29),
        Edge(2, 7, 34),
        Edge(6, 2, 40),
        Edge(3, 6, 52),
        Edge(6, 0, 58),
        Edge(6, 4, 93)
    };

    std::cout << "Kruskals" << std::endl;
    for (Edge e : kruskals(graph)) {
        std::cout << e.u << " " << e.v << std::endl;
    }

    std::cout << "Prims" << std::endl;
    for (Edge e : prims(graph)) {
        std::cout << e.u << " " << e.v << std::endl;
    }

    return 0;
}