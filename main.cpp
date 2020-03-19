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
