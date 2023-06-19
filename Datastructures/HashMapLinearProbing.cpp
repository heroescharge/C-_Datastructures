#include <iostream>

#define TOMBSTONE ((Pair) {(K) -INT32_MAX, (V) -INT32_MAX, false})

template <class K, class V>
class HashMap {
private:
    struct Pair {
        K key;
        V value;
        bool isNull;

        bool operator==(const Pair other) const {
            return key == other.key && value == other.value;
        }

        bool operator!=(const Pair other) const {
            return !(*this == other);
        }
    };

    struct Iterator {
        int index;
        int MAX_SIZE;
        Pair *table;
        Iterator(int index, Pair *table, int MAX_SIZE) {
            this->index = index;
            this->table = table;
            this->MAX_SIZE = MAX_SIZE;
        }

        K operator*() {
            return table[index].key;
        }
        K* operator->() {
            return &(table[index].key);
        }
        Iterator& operator++() {
            index++;
            while ((table[index].isNull || table[index] == TOMBSTONE) && index < MAX_SIZE) {
                index++;
            }
            return *this;
        }
        Iterator operator++(int) {
            Iterator it = *this;
            ++(*this);

            return it;
        }
        bool operator==(const Iterator other) const {
            return index == other.index;
        }
        bool operator!=(const Iterator other) const {
            return index != other.index;
        }
    };

    int MAX_SIZE;
    int numElements = 0;
    Pair *table;

public:
    HashMap(int MAX_SIZE) {
        this->MAX_SIZE = MAX_SIZE;
        table = new Pair[MAX_SIZE];
        for (int i = 0; i < MAX_SIZE; i++) {
            table[i].isNull = true;
        }
    }

    ~HashMap() {
        delete[] table;
    }

    int size() {
        return numElements;
    }

    bool isEmpty() {
        return size() == 0;
    }

    bool contains(K key) {
        int index = key % MAX_SIZE;
        while (!table[index].isNull) {
            if (table[index].key == key) {
                return true;
            }
            index = (index + 1) % MAX_SIZE;

            // Break if we go full circle
            if (index == key % MAX_SIZE) {
                break;
            }
        }

        return false;
    }

    void put(K key, V value) {
        if (size() > MAX_SIZE) { throw std::overflow_error("Table is full"); }
        
        int index = key % MAX_SIZE;
        if (contains(key)) {
            std::cout << "alr thre" << std::endl;
            while (table[index].key != key) {
                index = (index + 1) % MAX_SIZE;
            }

            table[index].value = value;
        }
        else {
            while (!table[index].isNull && table[index] != TOMBSTONE) {
                index = (index + 1) % MAX_SIZE;
            }

            table[index] = (Pair) {key, value, false};
            numElements++;
        }
    }

    V remove(K key) {
        int index = key % MAX_SIZE;
        while (!table[index].isNull) {
            if (table[index].key == key) {
                V value = table[index].value;
                table[index] = TOMBSTONE;
                numElements--;
                return value;
            }
            index = (index + 1) % MAX_SIZE;

            // Break if we go full circle
            if (index == key % MAX_SIZE) {
                break;
            }
        }

        throw std::out_of_range("No element found");
    }

    V get(K key) {
        int index = key % MAX_SIZE;
        while (!table[index].isNull) {
            if (table[index].key == key) {
                return table[index].value;
            }
            index = (index + 1) % MAX_SIZE;

            // Break if we go full circle
            if (index == key % MAX_SIZE) {
                break;
            }
        }

        throw std::out_of_range("No element found");
    }

    Iterator begin() {
        return Iterator(0, table, MAX_SIZE);
    }

    Iterator end() {
        return Iterator(MAX_SIZE, table, MAX_SIZE);
    }
};

int main() {
    HashMap<int, int> map(10);

    map.put(2, 3);
    map.put(12, 5);
    map.put(0, 9);
    map.put(4, 2);
    map.put(2, 6);

    std::cout << map.contains(2) << std::endl;
    std::cout << map.contains(7) << std::endl;
    std::cout << map.contains(42) << std::endl;
    std::cout << map.contains(0) << std::endl;

    std::cout << "Keys:" << std::endl;
    for (int k : map) {
        std::cout << k << std::endl;
    }

    std::cout << "Get values" << std::endl;
    std::cout << map.get(2) << std::endl;
    std::cout << map.get(12) << std::endl;
    std::cout << map.get(0) << std::endl;
    std::cout << map.get(4) << std::endl;

    std::cout << "Removed values" << std::endl;
    std::cout << map.remove(2) << std::endl;
    std::cout << map.remove(4) << std::endl;

    map.put(12, 4);

    std::cout << "Keys:" << std::endl;
    for (int k : map) {
        std::cout << k << std::endl;
    }

}