#include "AVL.h"

#include <vector>
#include <iostream>
#include <string>


using namespace std;

int height(AVLNode* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* newNode(Airport airport) {
    AVLNode* node = new AVLNode();
    node->airport = airport;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

AVLNode* insertAirport(AVLNode* node, Airport airport) {
    if (node == NULL)
        return(newNode(airport));

    if (airport.code < node->airport.code)
        node->left = insertAirport(node->left, airport);
    else if (airport.code > node->airport.code)
        node->right = insertAirport(node->right, airport);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

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

AVLNode* searchAirport(AVLNode* node, string code) {
    if (node == NULL || node->airport.code == code)
        return node;

    if (node->airport.code < code)
        return searchAirport(node->right, code);

    return searchAirport(node->left, code);
}

void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        cout << root->airport.code << " ";
        inorderTraversal(root->right);
    }
}


