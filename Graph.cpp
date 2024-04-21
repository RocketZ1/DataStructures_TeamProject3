#include "Graph.h"

using namespace std;

Graph::Graph() {
    adjacencyList = new AVLNode();
}

AVLNode* Graph::getRoot() {
    return adjacencyList;
}

void Graph::addConnection(AVLNode* origin, AVLNode* destination, int distance, int cost) {
    for (int i = 0; i < origin->airport.connections.size(); i++) {
        if (origin->airport.connections[i] == destination) {
            origin->airport.costs[i] = min(origin->airport.costs[i], cost);
            return;
        }
    }
    origin->airport.connections.push_back(destination);
    origin->airport.distances.push_back(distance);
    origin->airport.costs.push_back(cost);
}

void Graph::addAirport(Airport airport) {
    adjacencyList = insertAirport(adjacencyList, airport);
}

void Graph::addConnectionUndirected(AVLNode* origin, AVLNode* destination, int distance, int cost) {
    addConnection(origin, destination, distance, cost);
    addConnection(destination, origin, distance, cost);
}