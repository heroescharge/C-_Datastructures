#include <stdexcept>
#include <iostream>
#include <vector>

template <class K>
class IndexedPQ {
private:
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

struct TestOrder {
    int x;

    TestOrder() {
        this->x = -1;
    }

    TestOrder(int x) {
        this->x = x;
    }

    bool operator==(const TestOrder other) const {
        return abs(x) == abs(other.x);
    }
    bool operator!=(const TestOrder other) const {
        return !(*this == other);
    }
    bool operator>(const TestOrder other) const {
        return abs(x) > abs(other.x);
    }
    bool operator<(const TestOrder other) const {
        return !(*this > other);
    }
};

// // Unit testing
// int main() {
//     IndexedPQ pq = IndexedPQ<TestOrder>(10);
//     pq.insert(0, TestOrder(2));
//     pq.insert(1, TestOrder(3));
//     pq.insert(2, TestOrder(-1));
//     pq.insert(3, TestOrder(-6));
//     pq.insert(4, TestOrder(6));
//     std::cout << "Size: " << pq.size() << std::endl;

//     pq.changeKey(0, -12);
//     pq.changeKey(2, -88);
//     std::cout << "Size: " << pq.size() << std::endl;
//     std::cout << pq.pop();
//     std::cout << pq.pop();
//     std::cout << pq.pop();

//     return 0;
// }