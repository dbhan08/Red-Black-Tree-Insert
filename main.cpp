#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;










node* getSibling(node* find) {
    node * parent = find->getParent();
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


node* getUncle(node* find) {
    if(find != NULL) {
        node * parent = find->getParent();
        return getSibling(parent);
    } else {
        return NULL;
    }
}

node* getGrand(node * find) {
    node * parent = find->getParent();
    if(parent != NULL) {
        return parent->getParent();
    } else {
        return NULL;
    }
}


// Following function inserts into the tree, also from my binary search tree project
void insert(node* &root,node* head ,node* temp) {
    int RED = 0;
    int BLACK = 1;
    // If tree is empty
    if(root == NULL) {
        // Make it a new node
        root->setColor(RED);
        root = temp;
        temp->setParent(NULL);
        
    } else if(*temp->getValue() == *head->getValue()) {
        // If value is already in tree no need for another node
        return;
        
    } else if(*temp->getValue() < *head->getValue()) {
        // If new value is less then the current nodes value
        
        if(head->getLeft() == NULL) {
            // If the left is not null, make a new node with the given value
            
            temp->setColor(RED);
            head->setLeft(temp);
            temp->setParent(head);
            
        } else {
            // Transverse to the less
            insert(root, head->getLeft(),temp);
        }
    } else {
        //If given value is greater then current nodes value
        if(head->getRight() == NULL) {
            // If the right node is null make new node of the given value
            
            temp->setColor(RED);
            head->setRight(temp);
            temp->setParent(head);
            
        } else {
            // Transverse to the right
            insert(root,head->getRight(),temp);
        }
        
        
    }
    
    
    
    
}
// Pseudo code from https://www2.cs.duke.edu/courses/spring05/cps130/lectures/skiena.lectures/lecture10.pdf
void rotateLeft(node* root, node* temp) {
    node * y = temp->getRight();
    temp->setRight(y->getLeft());
    if(y->getLeft() != NULL) {
        y->getLeft()->setParent(temp);
        
    }
    y->setParent(temp->getParent());
    if(temp->getParent() == NULL) {
        root = y;
    } else if(temp == temp->getParent()->getLeft()) {
        temp->getParent()->setLeft(y);
    } else {
        temp->getParent()->setRight(y);
    }
    y->setLeft(temp);
    temp->setParent(y);
    
    
}





void rotateRight(node* root, node* temp) {
    node * y = temp->getLeft();
    temp->setRight(y->getRight());
    if(y->getRight() != NULL) {
        y->getRight()->setParent(temp);
        
    }
    y->setParent(temp->getParent());
    if(temp->getParent() == NULL) {
        root = y;
    } else if(temp == temp->getParent()->getLeft()) {
        temp->getParent()->setLeft(y);
    } else {
        temp->getParent()->setRight(y);
    }
    y->setRight(temp);
    temp->setParent(y);
    
    
}

void swapColor(node* first, node* second) {
    int firstColor = first->getColor();
    int secondColor = second->getColor();
    first->setColor(secondColor);
    second->setColor(firstColor);
}




void case5(node* root, node* temp) {
    if(getGrand(temp)->getRight() == temp->getParent() && temp->getParent()->getRight() == temp) {
        rotateLeft(root,getGrand(temp));
        swapColor(temp->getParent(),getGrand(temp));
    } else if(getGrand(temp)->getLeft() == temp->getParent() && temp->getParent()->getLeft() == temp) {
        rotateRight(root,getGrand(temp));
        swapColor(temp->getParent(),getGrand(temp));
    }
}



void repairAdd(node* root, node* temp) {
    int RED = 0;
    int BLACK = 1;
    if(temp->getParent() == NULL) {
        temp ->setColor(BLACK);
        return;
    } else if(temp->getParent()->getColor() == BLACK) {
        return;
    } else if(temp->getParent()->getColor() == RED && getUncle(temp)->getColor() == RED) {
        temp->getParent()->setColor(BLACK);
        getUncle(temp)->setColor(BLACK);
        getGrand(temp)->setColor(RED);
        repairAdd(root,getGrand(temp));
        
        
    } else if(getUncle(temp)->getColor() == BLACK || !getUncle(temp))   {
        
        if(getGrand(temp)->getLeft() == getUncle(temp)) {
            if(temp == temp->getParent()->getLeft()) {
                rotateLeft(root,temp->getParent());
                
            }
            
            
            
        } else if(getGrand(temp)->getRight() == getUncle(temp)) {
            if(temp==temp->getParent()->getRight()) {
                rotateRight(root,temp->getParent());
            }
        }
    
        case5(root,temp);
    
    }
}







void add(node* &root, int value) {
    node* temp = new node(value);
    insert(root,root,temp);
    
}










int main() {
return 0;


}
