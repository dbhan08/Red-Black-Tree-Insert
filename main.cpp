#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;



node *getParent(node* root, node* find) {
    if(find != NULL && root != NULL) {
        if(root->getLeft() == find || root->getRight() == find) {
            return root;
        } else if(*root->getValue() > *find->getValue()) {
            if(root->getLeft()) {
                return getParent(root->getLeft(),find);
            } else {
                return NULL;
            }
            
            
        } else if(*root->getValue() < *find->getValue()) {
            if(root->getRight()) {
                return getParent(root->getRight(),find);
            } else {
                return NULL;
            }
            
        } else {
            return NULL;
        }
        
    } else {
        return NULL;
    }
    
    
}




// Following function inserts into the tree, also from my binary search tree project
void insert(node* &root,node* head ,int value) {
    int RED = 0;
    int BLACK = 1;
    // If tree is empty
    if(root == NULL) {
        // Make it a new node
        root = new node(value);
        root->setColor(BLACK);
    } else if(value == *head->getValue()) {
        // If value is already in tree no need for another node
        return;
        
    } else if(value < *head->getValue()) {
        // If new value is less then the current nodes value
        
        if(head->getLeft() == NULL) {
            // If the left is not null, make a new node with the given value
            node *temp = new node(value);
            temp->setColor(RED);
            head->setLeft(temp);
            
        } else {
            // Transverse to the less
            insert(root, head->getLeft(),value);
        }
    } else {
        //If given value is greater then current nodes value
        if(head->getRight() == NULL) {
            // If the right node is null make new node of the given value
            node* temp = new node(value);
            temp->setColor(RED);
            head->setRight(temp);
            
        } else {
            // Transverse to the right
            insert(root,head->getRight(),value);
        }
        
        
    }
    
    
    
    
}



void add(node* &root, int value) {
    insert(root,root,value);
    
}


node* getSibling(node *root,node* find) {
    node * parent = getParent(root,find);
    if(parent != NULL) {
        if(parent->getLeft() == find) {
            return parent->getRight();
        } else {
            return parent->getLeft();
        }
    } else {
        return NULL;
    }
}


node* getUncle(node* root,node* find) {
    if(find != NULL) {
        node * parent = getParent(root,find);
        return getSibling(root,parent);
    } else {
        return NULL;
    }
}

node* getGrand(node* root, node * find) {
    node * parent = getParent(root,find);
    if(parent != NULL) {
        return getParent(root,parent);
    } else {
        return NULL;
    }
}









int main() {
return 0;


}
