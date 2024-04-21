#include "AVL.cpp"

using namespace std;

class Graph {
private:
    AVLNode* adjacencyList;
public:
    Graph();
    AVLNode* getRoot();
    void addConnection(AVLNode* origin, AVLNode* destination, int distance, int cost);
    void addAirport(Airport airport);
};

Graph::Graph() {
    adjacencyList = new AVLNode();
}

AVLNode* Graph::getRoot() {
    return adjacencyList;
}

void Graph::addConnection(AVLNode* origin, AVLNode* destination, int distance, int cost) {
    origin->airport.connections.push_back(destination);
    origin->airport.distances.push_back(distance);
    origin->airport.costs.push_back(cost);
}

void Graph::addAirport(Airport airport) {
    adjacencyList = insertAirport(adjacencyList, airport);
}