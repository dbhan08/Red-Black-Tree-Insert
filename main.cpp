/*
 Following Program is a red black-tree data structure which only includes the insert and the visulaize function for now.
 
 By:Deyvik Bhan
 Teacher:Mr.Galbraith
 
 
 */



#include <iostream>
#include <cstring>
#include "node.h"
#include <fstream>

using namespace std;






// Following function is the visualize function which is taken from my binary search tree with some modficications. Also ali Fakhry helped me with the binary search tree version

void visualize(node* head, int depth=0)

{
    int RED = 0;
    int BLACK = 1;
    if(head != NULL ) {
        
        if(head->getRight() != NULL) {
            //   cout << "a" << endl;
            //  cout << head->getRight() << endl;
            visualize(head->getRight(), depth+1);
            
        }
        // cout << "d" << endl;
        int temp = depth;
        
        while(depth > 0) {
            cout << "  ";
            depth --;
        }
        if(head != NULL) {
            
            
            if(head->getColor() == RED) {
                cout << *head->getValue() << "(RED)" << endl;
            } else {
                cout << *head->getValue() <<"(BLACK)"<< endl;
            }
            //    cout << "b" << endl;
            
        }
        
        if(head->getLeft() != NULL) {
            // cout << "c" << endl;
            visualize(head->getLeft(), temp+1);
            
            
        }
    }
    
    // cout << "kms" << endl;
}


// Following functin gets the sibling of a node in the tree

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



// Following function gets the uncle of a node in the tree
node* getUncle(node* find) {
    
    if(find != NULL) {
       
        node * parent = find->getParent();
        
        return getSibling(parent);
    } else {
        return NULL;
    }
    
}

// Following function gets the grand parent of a node in the tree

node* getGrand(node * find) {
    node * parent = find->getParent();
    if(parent != NULL) {
        return parent->getParent();
    } else {
        return NULL;
    }
}


// Following function inserts into the tree, also from my binary search tree project with some minor modifications
void insert(node* &root,node* head ,node* temp) {
    int RED = 0;
    int BLACK = 1;
    // If tree is empty
    if(root == NULL) {
       // cout << "a" << endl;
        // Make it a new node
        root = temp;
        root->setColor(RED);
        
        root->setParent(NULL);
        
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
void leftRotate(node* &root, node* nextNode)
{
 
    node* current = nextNode -> getRight();
    
    

        
        nextNode -> setRight(current -> getLeft());
        if(current -> getLeft() != NULL)
        {
            current -> getLeft() -> setParent(nextNode);
        }
         current -> setParent(nextNode -> getParent());
    
    
   
    if(nextNode == root)
    {
       
        
        root = current; //The new root is now the current
        
            }
    else
    {
        
        if(nextNode == nextNode -> getParent() -> getLeft())
        {
            nextNode -> getParent() -> setLeft(current);
        }
        else
        {
            nextNode -> getParent() -> setRight(current);
        }
    }
    
    current -> setLeft(nextNode);
    nextNode -> setParent(current);
    
}



//Pseudo code from https://www2.cs.duke.edu/courses/spring05/cps130/lectures/skiena.lectures/lecture10.pdf
void rightRotate(node* &root, node* nextNode)

{
   
    node* current = nextNode -> getLeft();
   
   
        nextNode -> setLeft(current -> getRight());
    
        if(current -> getRight() != NULL)
        {
            current -> getRight() -> setParent(nextNode); //set current's left to the parent of the nextNode (the inputted node)
        }
        current -> setParent(nextNode -> getParent());
   

    
    
    if(nextNode == root)
    {
      
        root = current; //The new root is now the current
    }
    else
    {
               if(nextNode == nextNode -> getParent() -> getLeft())
        {
            nextNode -> getParent() -> setLeft(current);
        }
        else
        {
            nextNode -> getParent() -> setRight(current);
        }
        
    }
   

        current -> setRight(nextNode);
   

    
        nextNode -> setParent(current);
    

}














// Following functions swaps colors between two nodes


void swapColor(node* first, node* second) {
    int firstColor = first->getColor();
    int secondColor = second->getColor();
    first->setColor(secondColor);
    second->setColor(firstColor);
  
}


// Following function is the fifth case which is either called after the fourth case or exclusively on its own

void case5(node* &root, node* temp) {
    
    if(getGrand(temp)->getRight() == temp->getParent() && temp->getParent()->getRight() == temp) {
       
        leftRotate(root,getGrand(temp));
        swapColor(temp->getParent(),getSibling(temp));
    } else if(getGrand(temp)->getLeft() == temp->getParent() && temp->getParent()->getLeft() == temp) {
        rightRotate(root,getGrand(temp));
        swapColor(temp->getParent(),getSibling(temp));
    }
}


// Following function recolors the tree appropriately
void repairAdd(node* &root, node* temp) {

    int RED = 0;
    int BLACK = 1;
    if(temp->getParent() == NULL) {
     
       
        temp ->setColor(BLACK);
        return;
    } else if(temp->getParent()->getColor() == BLACK) {
        
        return;
    } else if(getUncle(temp) != NULL && temp->getParent()->getColor() == RED && getUncle(temp)->getColor() == RED) {
      
        temp->getParent()->setColor(BLACK);
        getUncle(temp)->setColor(BLACK);
        getGrand(temp)->setColor(RED);
        repairAdd(root,getGrand(temp));
        
      
    } else if(!getUncle(temp) || getUncle(temp) ->getColor() == BLACK)   {
        
        
        if(getGrand(temp)->getLeft() == getUncle(temp)) {
            
            

            if(temp == temp->getParent()->getLeft()) {
                
                rightRotate(root,temp->getParent());
                
                 case5(root,temp->getRight());
                return;
                
            } else {
                case5(root,temp);
                return;
            }
            
        } else if(getGrand(temp)->getRight() == getUncle(temp)) {
        
        
            if(temp==temp->getParent()->getRight()) {
                leftRotate(root,temp->getParent());
                case5(root,temp->getLeft());
                return;
            } else {
            
            case5(root,temp);
                return;
        }
    
      
        }
    }
    
    
}




// Following function searches the tree and wfinds the value
node* search(node* root, int value) {
    
    if(root != NULL) {
        // If the tree is not empty
        if(value == *root->getValue()) {
            // If the current node has the same value as the value being searched for return the current node(node found)
            // cout << root->getValue() << "a" << endl;
                       return root;
            
            
            
            
        } else if(value < *root->getValue()) {
            // If value being searched for is less then the current nodes value
            
            if(root->getLeft() != NULL) {
                // If there is a left node transverse to that node and check if it is equal
                
                return search(root->getLeft(), value);
            } else {
                // There is no node that matches the value
                
                return NULL;
            }
        } else if(value > *root->getValue() ) {
            // If the value being searched for is greater then the current nodes value
            
            
            if(root->getRight() != NULL) {
                // If there is a right node transverse to that node and call the function
                //      cout << root->getRight()->getValue() << "c" << endl;
                return search(root->getRight(), value);
                
            } else {
                // There is no node that matches the values
                //  cout << "k" << endl;
                return NULL;
            }
        } else {
            
            return NULL;
        }
    } else {
        return NULL;
    }
    
    
}












void ReplaceNode(node* parent, node* child) {
    
    if(child != NULL) {
        child->setParent(parent->getParent());
    }
    if (parent == parent->getParent()->getLeft()) {
        parent->getParent()->setLeft(child);
    } else {
        parent->getParent()->setRight(child);
    }
    
}

// Function reblances the tree for removing

void fixRemove(node* & root,node* n, int side)
{
    

    if(n->getParent() != NULL)
    {
       
        if(getSibling(n) ->getColor() == 0)
        {
          
            getSibling(n)->setColor(1);
            n->getParent()->setColor(0);
            
            
      
            if(side == 1) {
                rightRotate(root,n->getParent());
            }else {
                leftRotate(root,n->getParent());
            }
            
            
        }
        
        
        if(getSibling(n)->getRight()->getColor() == 1 && getSibling(n)->getLeft()->getColor() == 1)
        {
        
            if(n->getParent()->getColor() == 1)
            {
                
                getSibling(n)->setColor(0);
                
                
                if(getGrand(n) == NULL) {
                    fixRemove(root,n->getParent(), 2);
                } else if(getGrand(n)->getRight() == n->getParent()) {
                    fixRemove(root,n->getParent(), 1);
                } else{
                    fixRemove(root,n->getParent(), 0);
                }
                
                return;
            }
            
          
            else
            {
               
                n->getParent()->setColor(1);
                getSibling(n)->setColor(0);
               
                
                return;
            }
        }
  
        if(side == 1 && getSibling(n)->getLeft()->getColor() == 1 && getSibling(n)->getRight()->getColor() == 0)
        {
            getSibling(n)->getRight()->setColor(1);
            getSibling(n)->setColor(0);
           leftRotate(root,getSibling(n));
        }
        else if(side == 0 && getSibling(n)->getRight()->getColor() == 1 && getSibling(n)->getLeft()->getColor() == 1)
        {
            getSibling(n)->getLeft()->setColor(1);
            getSibling(n)->setColor(0);
            rightRotate(root,getSibling(n));
        }
        
        
        getSibling(n)->setColor(n->getParent()->getColor());
       
      n->getParent()->setColor(1);
        if(side == 1)
        {
            getSibling(n)->getLeft()->setColor(1);
            
            rightRotate(root,n->getParent());
        }
        else
        {
            getSibling(n)->getRight()->setColor(1);
            leftRotate(root,n->getParent());
        }
    }
}

// Functions removes numbers from the rbt
node* remove(node* &root, int value)
{
  node* temp = search(root, value);
   
    if(temp != NULL)
    {
      
        if(temp->getRight() != NULL && temp->getLeft() != NULL)
        {
         
            node* replace = temp->getLeft();
            while(replace->getRight() != NULL) {
                replace = replace->getRight();
            
            }
          
            temp->setValue(*(replace->getValue()));
            temp = replace;
        }
        
        int side = 0;
        if(temp->getParent()->getLeft() == temp) {
            side = 0;
        } else {
            side = 1;
        }
                           
        
        if(temp ->getColor() != 1)
        {
            if(side == 1)
                temp->getParent()->setRight(NULL);
            else if(side == 0)
                temp->getParent()->setLeft(NULL);
        }
        
     
        else if(temp->getRight() || temp->getLeft())
            
        {
            node* child;
            if(temp->getLeft() != NULL) {
                node* child = temp->getLeft();
            } else {
                node* child = temp->getRight();
            }
            child->setColor(1);
            ReplaceNode(temp,child);
        }
        
      
        else
        {
            fixRemove(root,temp, side);
        }
        
        
        if(temp->getParent() == NULL)
        {
            temp->setValue(0);
        }
        
        else
        {
            if(side == 1 && temp->getParent() != NULL) {
                temp->getParent()->setRight(NULL);
            }
            else if(side == 0 && temp->getParent()) {
                temp->getParent()->setLeft(NULL);
            }
            
            free(temp);
        }
        
    }
   
    else
    {
        cout << "That number is not in the tree.\n";
    }
    
    while(root->getParent() != NULL) {
        root = root->getParent();
    }
    return root;
}







// Following function Taken from stefan ene
void parse(char* in, int* modif, int &count) {
    int l = 0;  //keeps track of # of chars before space
    for (int i = 0; i < strlen(in); i++) {
        if (in[i] == ' ') {
            if (l == 1) {
                int temp = 0;
                temp = in[i-1] - '0';
                modif[count] = temp;
                count++;
                l = 0;
            } else {
                int temp = 0;
                for (int a = 0; a < l; a++) {
                    temp = 10 * temp + (in[i-l+a] - '0');
                }
                modif[count] = temp;
                count++;
                l = 0;
            }
        } else {
            int temp = 0;
            l++;
            if (i == strlen(in) - 1) {  //last possible pair of chars
                for (int a = 0; a < l; a++) {
                    temp = 10 * temp + (in[i+a+1-l] - '0');
                }
                modif[count] = temp;
                count++;
            }
        }
    }
}






// Following function combines the binary search tree add and the tree adjustment to make the red-black tree
void add(node* &root, int value) {
    node* temp = new node(value);
    insert(root,root,temp);
    
    repairAdd(root,temp);
    
}







// From my binary search tree as well, some code taken from stefan, and the file stuff is taken from OMar Nassar

int main() {
    
    // The main function jsut takes care of basic input stuff
    // Just the input stuff
    node* root = new node(0);
    node* curr = new node(0);
    curr = NULL;
    root = NULL;
    int count = 0;
    int modif[100];
    char fileName[30];
    
    for (int i = 0; i < 100; i++) {
        modif[i] = 0;
    }
    
    cout << "If you would like to input manually type '1' if you would like to do it from a file type '2':" << endl;
    char inp[10];
    char input[100000];
    cin.get(inp,10);
    cin.clear();
    cin.ignore(1000000,'\n');
    if(strcmp(inp,"1")== 0) {
        cout << "Enter a set of numbers sperated by spaces:" << endl;
        char in[100000];
        cin.get(in, 100000);
        cin.clear();
        cin.ignore(1000000, '\n');
        parse(in,modif,count);
        
        for(int i = 0; modif[i] != 0; i++) {
            
            add(root,modif[i]);
        }
        //cout << root->getValue() << endl;
        visualize(root,0);
        // int size = sizeof(modif)/sizeof(modif[0]);
        
        
        
    } else if(strcmp(inp,"2")== 0) {
        
        // Following chunk from Omar Nassar
        cout << endl << "What is the name of the file?" << endl << ">> ";
        cin.get(fileName, 30);
        cin.clear();
        cin.ignore(100000, '\n');
        streampos size;
        ifstream file(fileName, ios::in | ios::binary | ios::ate);
        if (file.is_open()) {
            size = file.tellg();
            file.seekg(0, ios::beg);
            file.read(input, size);
            file.close();
            parse(input,modif,count);
            for(int i = 0; modif[i] != 0; i++) {
                    add(root,modif[i]);
            }
            visualize(root,0);
            //cout << root->ge
            
            
            
            // int size = sizeof(modif)/sizeof(modif[0]);
            
            
        }
        
        
    } else {
        cout << "Enter a valid option!" << endl;
    }
    
    
    bool running = true;
    while(running) {
        cout << "Would you like to 'insert', 'delete', 'search', or quit?" << endl;
        char inp[50];
        cin.get(inp,50);
        cin.clear();
        cin.ignore(50,'\n');
        if(strcmp(inp, "insert") == 0)  {
            cout << "What would you like to Insert" << endl;
            char inp[100];
            cin.get(inp,100);
            cin.clear();
            cin.ignore(100,'\n');
            int a = atoi(inp);
            
            add(root,a);
            visualize(root,0);
            
            
            
            
        } else if(strcmp(inp, "search") == 0) {
            
            cout << "What would you like to search for" << endl;
            char inp[100];
            cin.get(inp,100);
            cin.clear();
            cin.ignore(100,'\n');
            int a = atoi(inp);
            
            //  cout << *root->getValue() << endl;
            
            //  cout << *search(root,a) ->getValue() << "l" << endl;
            //   cout << search(root,a) << "n" << endl;
            
            if( search(root,a) != NULL) {
                
                cout << "The number was found!" << endl;
            } else {
                //  cout << search(root,a) << endl;
                cout << "Number not in tree!" << endl;
            }
            
            //  cout << root->getValue()  << "z" << endl;
            
        } else if(strcmp(inp, "delete") == 0) {
            char inp[100];
            cin.get(inp,100);
            cin.clear();
            cin.ignore(100,'\n');
            int a = atoi(inp);
            
            remove(root,a);
           
       
            visualize(root,0);
            
        } else if(strcmp(inp, "quit") == 0) {
            running = false;
        } else {
            cout << "Enter a valid option" << endl;;
        }
    }
    
    
    
    
    
    
    
    
    return 0;

}



