#ifndef AVL_H
#define AVL_H

#include <string>
#include <vector>

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
public:
    Airport airport;
    AVLNode* left;
    AVLNode* right;
    int height;
};

int height(AVLNode* N);

int max(int a, int b);

AVLNode* newNode(Airport airport);

AVLNode* rightRotate(AVLNode* y);

AVLNode* leftRotate(AVLNode* x);

int getBalance(AVLNode* N);

AVLNode* insertAirport(AVLNode* node, Airport airport);

AVLNode* searchAirport(AVLNode* node, string code);

void inorderTraversal(AVLNode* root);

int size(AVLNode* root);

#endif