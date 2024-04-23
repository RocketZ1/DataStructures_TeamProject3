#include <string>
#include <iostream>
#include <utility>

// A structure to represent a node in the min heap
struct SearchNode {
    std::string code;
    std::string origin;
    int distance{};
    bool visited{};
    int stops{};
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
    // Insert a node with a given code, origin, and distance
    void insert(std::string str, std::string origin, int dist) {
        if (size == capacity) {
            std::cout << "Minheap Overflow" << std::endl;
            return;
        }

        arr[size].code = str;
        arr[size].origin = origin;
        arr[size].distance = dist;
        size++;

        percolateUp(size - 1);
    }
    // Insert a node with a given code and distance
    void insert(std::string str, int dist) {
        if (size == capacity) {
            std::cout << "Minheap Overflow" << std::endl;
            return;
        }

        arr[size].code = str;

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
    // get the index of the minimum value
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
    // Get the minimum node
    SearchNode getMin() {
        if (size <= 0) {
            std::cout << "Heap is empty" << std::endl;
            throw 505;
        }
//
//        while(arr[0].visited) {
//            arr[0] = arr[size - 1];
//            size--;
//            percolateDown(0);
//        }

        SearchNode minNode = arr[0];
        arr[0] = arr[size - 1];
        size--;
        percolateDown(0);

        return minNode;
    }
    // Check if the heap is empty
    bool isEmpty() {
        return (size <= 0);
    }
    // Visit all nodes with the given code
    SearchNode popMin() {
        if (size <= 0) {
            std::cout << "Heap is empty" << std::endl;
            return SearchNode();
        }
        // Remove the visited nodes
        while(arr[0].visited) {
            arr[0] = arr[size - 1];
            size--;
            percolateDown(0);
        }

        if (size <= 0) {
        std::cout << "All nodes are visited" << std::endl;
        return SearchNode(); // Assuming SearchNode() creates a default node
        }

        SearchNode min = arr[0];
        arr[0] = arr[size - 1];
        size--;
        percolateDown(0);

        return min;
    }
    // Visit all nodes with the given code
    void visit (std::string code) {
        for (int i = 0; i < size; i++) {
            if (arr[i].code == code) {
                arr[i].visited = true;
                return;
            }
        }
    }
    // Check if the node is visited
    bool isVisited(std::string code) {
        for (int i = 0; i < size; i++) {
            if (arr[i].code == code) {
                return arr[i].visited;
            }
        }
        return false;
    }

};
