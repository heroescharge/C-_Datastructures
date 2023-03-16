#include <cstdlib>
#include <ctime>

// Randomly permute all elements from begin to end
template <class RandomIt>
void shuffle(RandomIt begin, RandomIt end) {
    int numElement = 0;
    for (RandomIt i = begin; i != end; i++) {
        numElement++;
        std::srand((unsigned int)time(NULL));
        std::swap(*i, *(i - std::rand() % numElement));
    }
}

template <class T>
void merge(T arr[], int begin, int mid, int end) {
    T arrCopy[end - begin + 1];
    int lIndex = begin, rIndex = mid + 1;
    int copyIndex = 0;
    while (lIndex <= mid && rIndex <= end) {
        if (arr[lIndex] < arr[rIndex]) {
            arrCopy[copyIndex++] = arr[lIndex++];
        }
        else {
            arrCopy[copyIndex++] = arr[rIndex++];
        }
    }

    while (lIndex <= mid) {
        arrCopy[copyIndex++] = arr[lIndex++];
    }
    while (rIndex <= end) {
        arrCopy[copyIndex++] = arr[rIndex++];
    }

    for (int i = 0; i < end - begin + 1; i++) {
        arr[begin + i] = arrCopy[i];
    }
}

// Sort arr from index begin to end inclusive
template <class T>
void mergesort(T arr[], int begin, int end) {
    if (begin == end) {
        return;
    }
    int mid = begin + (end - begin) / 2;
    mergesort(arr, begin, mid);
    mergesort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}