#include <iostream>
#include "Sorting.cpp" // couldn't be bothered to make a header file

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

void test_shellshort() {
    int arr[] = {1, 11, 2, 9, 5, 8, 9, 13, 7, -4, -6};
    shellshort(arr, 0, 11);
    for (int i = 0; i < 11; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void test_quicksort() {
    int arr[] = {10, 0, 9, 1, 8, 2, 7, 3, 6, 4, 5};
    quicksort(arr, 0, 10);
    for (int i = 0; i < 11; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // test_shuffle();
    // test_mergesort();
    // test_shellshort();
    test_quicksort();
}