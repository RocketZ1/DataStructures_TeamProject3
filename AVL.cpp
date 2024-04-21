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
    AVLNode(Airport &airport) {
        this->airport = airport;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0;
    }

    int getHeight() {
        return this->height;
    }

    int getBalanceFactor() {
        int leftHeight = 0, rightHeight = 0;
        this->left == nullptr ? 0 : leftHeight = left->getHeight();
        this->right == nullptr ? 0 : rightHeight = right->getHeight();
        return leftHeight - rightHeight;
    }

    AVLNode* getLeft(){
        return this->left;
    }

    AVLNode* getRight(){
        return this->right;
    }

    Airport getAirport(){
        return this->airport;
    }

    AVLNode* rightRotate() {
        AVLNode* newRoot = this->left;
        AVLNode* temp = this->right;

        newRoot->right = this;
        this->left = temp;

        // Fixed NULL segmentation error height code
        int leftHeight = 0;
        int rightHeight = 0;
        if(this->left != nullptr){
            leftHeight = this->left->getHeight();
        }
        if(this->right != nullptr){
            rightHeight = this->right->getHeight();
        }
        this->height = 1 + max(leftHeight, rightHeight);
        //this->height = 1 + max(this->left->getHeight(), this->right->getHeight());
        // reset both height variables to 0
        leftHeight = rightHeight = 0;
        if(newRoot->left != nullptr){
            leftHeight = newRoot->left->getHeight();
        }
        if(newRoot->right != nullptr){
            rightHeight = newRoot->right->getHeight();
        }
        newRoot->height = 1 + max(leftHeight, rightHeight);
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

    void addConnection(AVLNode* origin, AVLNode* destination, int distance, int cost) {;
        origin->airport.connections.push_back(destination);
        origin->airport.distances.push_back(distance);
        origin->airport.costs.push_back(cost);
    }

    AVLNode* insertAirport(Airport &airport) {
        if(this->airport.code.empty()){
            this->airport = airport;
            this->height = 1;
            return this;
        }

        AVLNode* newNode;
        if (airport.code < this->airport.code) {
            if (this->left == nullptr) {
                this->left = new AVLNode(airport);
                newNode = this->left;
            } else {
                newNode = this->left->insertAirport(airport);
            }
        } else if (airport.code > this->airport.code) {
            if (this->right == nullptr) {
                this->right = new AVLNode(airport);
                newNode = this->right;
            } else {
                newNode = this->right->insertAirport(airport);
            }
        }
        else {
            return this;
        }
        int leftHeight = 0;
        int rightHeight = 0;
        if(this->left != nullptr){
            leftHeight = this->left->getHeight();
        }
        if(this->right != nullptr){
            rightHeight = this->right->getHeight();
        }
        this->height = 1 + max(leftHeight, rightHeight);

        int balanceFactor = getBalanceFactor();

        if (balanceFactor > 1) {
            this->rightRotate();
        }
        return newNode;
    }


};

struct SearchNode {
    std::string code;
    int distance;
    bool visited;
}