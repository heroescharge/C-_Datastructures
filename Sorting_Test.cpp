#include <iostream>
#include "Sorting.cpp"

void test_shuffle() {
    int arr[] = {1, 2, 5, 8, 9};
    shuffle(arr, arr + 5);
    for (int i = 0; i < 5; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void test_mergesort() {
    int arr[] = {1, 11, 2, 9, 5, 8, 9};
    mergesort(arr, 0, 6);
    for (int i = 0; i < 7; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // test_shuffle();
    // test_mergesort();
}