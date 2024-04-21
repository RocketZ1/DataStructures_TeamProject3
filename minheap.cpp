#include <string>
#include <iostream>

class MinHeap {
    std::string* arr;
    int capacity;
    int size;

    public:

    MinHeap(int capacity) {
        this->capacity = capacity;
        size = 0;
        arr = new std::string[capacity];
    }

    void insert(std::string str) {
        if (size == capacity) {
            std::cout << " Minheap Overflow" << std::endl;
            return;
        }

        size++;
        arr[size] = str;

        percolateUp(size);
    }

    void percolateUp(int index) {
        if (index < 1) {
            return;
        }

        if (arr[index / 2] > arr[index]) {
            swap(index, index / 2);
            percolateUp(index / 2);
        } 
    }

    void swap(int i, int j) {
        int temp = harr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
};