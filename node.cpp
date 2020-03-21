#include "node.h"
#include <iostream>

using namespace std;

// Constructor
node::node(int newValue) {
    value = newValue;
    left = NULL;
    right = NULL;
    
    
}


node::~node() {
    
    delete left;
    delete right;
    
}
// Sets left node
void node::setLeft(node* newLeft) {
    left = newLeft;
    
}
// Sets right node
void node::setRight(node* newRight) {
    right = newRight;
    
}
// Returns left node
node* node::getLeft() {
    return left;
}
// Returns right node
node* node::getRight() {
    return right;
}
// Returns value of node
int* node::getValue() {
    return &value;
}

// A way of changing the value of a node
void node::setValue(int newValue) {
    value =  newValue;
}

void node::setColor(int newColor) {
    color = newColor;
}

int node::getColor() {
    return color;
}

