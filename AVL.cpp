#include "AVL.h"
#include <vector>
#include <iostream>
#include <string>


using namespace std;
// Returns the height of the AVL tree
int height(AVLNode* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}
// Creates a new node with the given airport
AVLNode* newNode(Airport airport) {
    AVLNode* node = new AVLNode();
    node->airport = airport;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

// Rotates the AVL tree to the right
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotates the AVL tree to the left
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Returns the balance of the AVL tree
int getBalance(AVLNode* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Inserts an airport into the AVL tree
AVLNode* insertAirport(AVLNode* node, Airport airport) {
    if (node == NULL)
        return(newNode(airport));
    // Insert the airport into the AVL tree
    if (airport.code < node->airport.code)
        node->left = insertAirport(node->left, airport);
    else if (airport.code > node->airport.code)
        node->right = insertAirport(node->right, airport);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Determine the rotation needed
    if (balance > 1 && airport.code < node->left->airport.code)
        return rightRotate(node);

    if (balance < -1 && airport.code > node->right->airport.code)
        return leftRotate(node);

    if (balance > 1 && airport.code > node->left->airport.code) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && airport.code < node->right->airport.code) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Searches for an airport in the AVL tree
AVLNode* searchAirport(AVLNode* node, string code) {
    if (node == NULL || node->airport.code == code)
        return node;

    if (node->airport.code < code)
        return searchAirport(node->right, code);
    else
        return searchAirport(node->left, code);
}

// Traverses the AVL tree in order
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        cout << root->airport.code << " ";
        inorderTraversal(root->right);
    }
}

// Pushes the airport codes to a vector
void pushAirportCodesToVector(AVLNode* root, std::vector<SearchNode>& v) {
    if (root != NULL) {
        pushAirportCodesToVector(root->left, v);
        SearchNode node;
        node.code = root->airport.code;
        v.push_back(node);
        pushAirportCodesToVector(root->right,v);
    }
}

// Returns the size of the AVL tree
int size(AVLNode* root) {
    if (root == NULL) {
        return 0;
    }
    return size(root->left) + size(root->right) + 1;
}


