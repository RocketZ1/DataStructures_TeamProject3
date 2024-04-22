#include <string>
#include <iostream>
#include <utility>

struct SearchNode {
    std::string code;
    int distance{};
    bool visited{};
};

class MinHeap {
public:
    SearchNode* arr;
    int capacity;
    int size;

    MinHeap(int capacity) {
        this->capacity = capacity;
        size = 0;
        arr = new SearchNode[capacity];
    }

    ~MinHeap() {
        delete[] arr;
    }

    void insert(std::string str, int dist) {
        if (size == capacity) {
            std::cout << "Minheap Overflow" << std::endl;
            return;
        }

        arr[size].code = std::move(str);
        arr[size].distance = dist;
        size++;

        percolateUp(size - 1);
    }

    void percolateUp(int index) {
        while (index > 0 && arr[(index - 1) / 2].distance > arr[index].distance) {
            swap(index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
    }

    void swap(int i, int j) {
        SearchNode temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    int minimum(int a, int indexa, int b, int indexb) {
        return (a < b) ? indexa : indexb;
    }

    void percolateDown(int index) {
        while (2 * index + 1 < size) {
            int minChildIndex = minimum(arr[2 * index + 1].distance, 2 * index + 1, arr[2 * index + 2].distance, 2 * index + 2);
            if (arr[index].distance <= arr[minChildIndex].distance) break;
            swap(index, minChildIndex);
            index = minChildIndex;
        }
    }

    int getMin() {
        if (size <= 0) {
            std::cout << "Heap is empty" << std::endl;
            return -1;
        }

        int min = arr[0].distance;
        arr[0] = arr[size - 1];
        size--;
        percolateDown(0);

        return min;
    }
};
