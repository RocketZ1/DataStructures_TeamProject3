#include "Graph.h"

using namespace std;

Graph::Graph() {
    // Initialize the adjacency list with an empty node
    adjacencyList = new AVLNode();
}

AVLNode* Graph::getRoot() {
    // Return the root of the adjacency list
    return adjacencyList;
}

// Add a connection from origin to destination with a given distance and cost
void Graph::addConnection(AVLNode* origin, AVLNode* destination, int distance, int cost) {
    // Check if the connection already exists
    for (int i = 0; i < origin->airport.connections.size(); i++) {
        if (origin->airport.connections[i] == destination) {
            origin->airport.costs[i] = min(origin->airport.costs[i], cost);
            return;
        }
    }
    // Add the connection to the origin node
    origin->airport.connections.push_back(destination);
    origin->airport.distances.push_back(distance);
    origin->airport.costs.push_back(cost);
}

// Add an airport to the adjacency list
void Graph::addAirport(Airport airport) {
    adjacencyList = insertAirport(adjacencyList, airport);
}

// Add a connection from origin to destination and from destination to origin with a given distance and cost
void Graph::addConnectionUndirected(AVLNode* origin, AVLNode* destination, int distance, int cost) {
    addConnection(origin, destination, distance, cost);
    addConnection(destination, origin, distance, cost);
}