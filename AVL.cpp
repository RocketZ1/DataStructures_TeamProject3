#include <vector>
#include <iostream>
#include <string>

using namespace std;

class AVLNode;

struct Airport {
    string code;
    string city;
    vector<AVLNode*> connections;
    vector<int> distances;
    vector<int> costs;
};

class AVLNode {
private:
    Airport airport;
    AVLNode* left;
    AVLNode* right;
    int height;
public:
    AVLNode() {
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0;
    }
    AVLNode(Airport airport) {
        this->airport = airport;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0;
    }

    int getHeight() {
        return this->height;
    }

    int getBalanceFactor() {
        return this->left->getHeight() - this->right->getHeight();
    }

    AVLNode* rightRotate() {
        AVLNode* newRoot = this->left;
        AVLNode* temp = newRoot->right;

        newRoot->right = this;
        this->left = temp;

        this->height = 1 + max(this->left->getHeight(), this->right->getHeight());
        newRoot->height = 1 + max(newRoot->left->getHeight(), newRoot->right->getHeight());

        return newRoot;
    }

    AVLNode* leftRotate() {
        AVLNode* newRoot = this->right;
        AVLNode* temp = newRoot->left;

        newRoot->left = this;
        this->right = temp;

        this->height = 1 + max(this->left->getHeight(), this->right->getHeight());
        newRoot->height = 1 + max(newRoot->left->getHeight(), newRoot->right->getHeight());

        return newRoot;
    }

    void addConnection(AVLNode* airport, int distance, int cost) {;
        this->airport.connections.push_back(airport);
        this->airport.distances.push_back(distance);
        this->airport.costs.push_back(cost);
    }
    AVLNode* insertAirport(Airport airport) {
        AVLNode* newNode = nullptr;
        if (airport.code < this->airport.code) {
            if (this->left == nullptr) {
                this->left = new AVLNode(airport);
                newNode = this->left;
            } else {
                this->left->insertAirport(airport);
            }
        } else if (airport.code > this->airport.code) {
            if (this->right == nullptr) {
                this->right = new AVLNode(airport);
                newNode = this->right;
            } else {
                this->right->insertAirport(airport);
            }
        }
        else {
            return this;
        }
        this->height = 1 + max(this->left->getHeight(), this->right->getHeight());

        int balanceFactor = this->getBalanceFactor();

        if (balanceFactor > 1) {
            this->rightRotate();
        }
    }
};