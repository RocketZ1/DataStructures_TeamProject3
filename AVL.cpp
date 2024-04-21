#include <vector>
#include <iostream>
#include <string>

class AVLNode;

struct Airport {
    std::string code;
    std::string city;
    std::vector<AVLNode*> connections;
    std::vector<int> distances;
    std::vector<int> costs;
};

class AVLNode {
private:
    Airport airport;
    AVLNode* left;
    AVLNode* right;
    int height;
public:
    AVLNode(Airport airport) {
        this->airport = airport;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
    void addConnection(Airport airport, int distance, int cost) {
        AVLNode* newNode = new AVLNode(airport);
        airport.connections.push_back(newNode);
        airport.distances.push_back(distance);
        airport.costs.push_back(cost);
    }
    AVLNode insertAirport()
    {
        
    }
};