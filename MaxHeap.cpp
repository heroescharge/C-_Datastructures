#include <iostream>
#include <vector>

template <class T>
class MaxHeap {
private:
    std::vector<T> heap;

    void sink(int i) {
        while (2 * i <= heap.size() - 1) {
            if (2 * i + 1 <= heap.size() - 1 && heap[2 * i + 1] > heap[2 * i]) {
                if (heap[i] < heap[2 * i + 1]) {
                    std::swap(heap[i], heap[2 * i + 1]);
                    i = 2 * i + 1;
                }
                else {
                    break;
                }
            }
            else {
                if (heap[i] < heap[2 * i]) {
                    std::swap(heap[i], heap[2 * i]);
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
            if (heap[i] > heap[i / 2]) {
                std::swap(heap[i], heap[i / 2]);
                i /= 2;
            }
            else {
                break;
            }
        }
    }

public:
    MaxHeap() {
        heap.push_back((T) NULL); // First element is null; start at index 1
    }

    int size() {
        return heap.size() - 1;
    }

    bool isEmpty() {
        return size() == 0;
    }

    void insert(T value) {
        heap.push_back(value);
        swim(heap.size() - 1);
    }

    T pop() {
        if (isEmpty()) { throw std::underflow_error("Heap is empty"); }

        T value = heap[1];
        std::swap(heap[1], heap[heap.size() - 1]);
        heap.erase(heap.begin() + (heap.size() - 1));
        sink(1);

        return value;
    }

    T peek() {
        if (isEmpty()) { throw std::underflow_error("Heap is empty"); }

        return heap[1];
    }

    void print() {
        for (int i = 1; i < heap.size(); i++) {
            std::cout << heap[i] << " ";
        }
    }

};

int main() {
    MaxHeap<int> heap;
    heap.insert(2);
    heap.insert(4);
    heap.insert(1);
    heap.insert(8);
    heap.insert(11);
    heap.insert(3);
    heap.insert(2);
    heap.insert(10);
    heap.insert(-2);
    heap.insert(-2);
    heap.insert(11);
    std::cout << "Size: " << heap.size() << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << heap.peek() << " " << heap.pop() << std::endl;
    }
    std::cout << "Size: " << heap.size() << std::endl;
    heap.insert(8);
    heap.insert(11);
    heap.insert(3);
    heap.insert(2);
    for (int i = 0; i < 10; i++) {
        std::cout << heap.peek() << " " << heap.pop() << std::endl;
    }
    
    return 0;
}