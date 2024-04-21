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

    int MinHeap::minimum(int a, int indexa, int b, int indexb) {
        if (a < b) {
             return indexa;
        }
       
        return indexb;
    }

    void percolateDown(int index) {
        if ((2 * index + 1) <= heapSize) {

            std::string min = minimum(arr[2 * index], 2 * index, arr[2 * index + 1], 2 * index + 1);

            if (harr[index] > harr[min]) {
                swap(index, min);
                percolateDown(min);
            }   
        }

        else if (heapSize == 2 * index) {
            if (harr[index] > harr[2 * index]) {
                swap(index, 2 * index);
            }
        }
    }

    std::string getMin() {
        if (size <= 0) {
            return "ERROR";
        }

        std::string min = arr[0];
        arr[1] = arr[size];
        size--;
        percolateDown(1);
        
        return min;
    }

};
