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

template <class T>
void shellshort2(T arr[], int begin, int end, int h) {
    for (int offset = 0; offset < h; offset++) {
        for (int i = begin + h + offset; i < end; i+=h) {
            int j = i;
            while (j - h >= 0 && arr[j] < arr[j - h]) {
                std::swap(arr[j], arr[j - h]);
                j -= h;
            }
        }
    }
}

// Sort arr with shellshort, including begin and not including end
template <class T>
void shellshort(T arr[], int begin, int end) {
    int h = 1;
    while (h < (end - begin + 1) / 3) {
        h = 3 * h + 1;
    }

    while (h > 0) {
        shellshort2(arr, begin, end, h);
        h /= 3;
    }
}


// Quicksort from beginning to end inclusive
template <class T>
void quicksort(T arr[], int begin, int end) {
    if (begin == end) {
        return;
    }
    int lIndex = begin + 1;
    int rIndex = end;
    
    int pivot = arr[begin];

    while (lIndex <= rIndex) {
        while (arr[lIndex] <= pivot && lIndex <= end) {
            lIndex++;
        }
        while (arr[rIndex] >= pivot && rIndex >= begin + 1) {
            rIndex--;
        }
        if (lIndex < rIndex) {
            std::swap(arr[lIndex], arr[rIndex]);
        }
    }
    
    std::swap(arr[begin], arr[rIndex]);
    
    if (rIndex > begin) {
        quicksort(arr, begin, rIndex - 1);
    }
    if (lIndex <= end) {
        quicksort(arr, lIndex, end);
    }
}
