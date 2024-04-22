#ifndef GRAPH_H
#define GRAPH_H

#include "AVL.h"

using namespace std;

class Graph {
private:
    AVLNode* adjacencyList;
public:
    Graph();
    AVLNode* getRoot();
    void addConnection(AVLNode* origin, AVLNode* destination, int distance, int cost);
    void addAirport(Airport airport);
    void addConnectionUndirected(AVLNode* origin, AVLNode* destination, int distance, int cost);
};

#endif