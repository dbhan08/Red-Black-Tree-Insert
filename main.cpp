#include <iostream>
#include <cstring>
#include "node.h"
#include <fstream>

using namespace std;





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
       // cout << "a" << endl;
        // Make it a new node
        root = temp;
        root->setColor(RED);
        
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
/*
// Pseudo code from https://www2.cs.duke.edu/courses/spring05/cps130/lectures/skiena.lectures/lecture10.pdf
void rotateLeft(node* &root, node* temp) {
    
    node * y = temp->getRight();
    cout << y;
    temp->setRight(y->getLeft());
    cout << "e" << endl;
    
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
 */

// Pseudo code from https://www2.cs.duke.edu/courses/spring05/cps130/lectures/skiena.lectures/lecture10.pdf
void leftRotate(node* &root, node* nextNode)
{
    node* current = nextNode -> getRight();
    
    

        
        nextNode -> setRight(current -> getLeft());
        if(current -> getLeft() != NULL)
        {
            current -> getLeft() -> setParent(nextNode); //set current's left to the parent of the nextNode (the inputted node)
        }
         current -> setParent(nextNode -> getParent());
    
    
   
    if(nextNode == root)
    {
       ;
        
        root = current; //The new root is now the current
        cout << *root->getValue() << "kms"<< endl;
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
        cout << "x" << endl;
        root = current; //The new root is now the current
    }
    else
    {
        cout << "g" << endl;
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










/*

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
*/







void swapColor(node* first, node* second) {
    int firstColor = first->getColor();
    int secondColor = second->getColor();
    first->setColor(secondColor);
    second->setColor(firstColor);
}




void case5(node* root, node* temp) {
    
    if(getGrand(temp)->getRight() == temp->getParent() && temp->getParent()->getRight() == temp) {
        cout << *getGrand(temp)->getValue() << "k" << endl;
        cout << *temp->getValue() << "f" << endl;
        leftRotate(root,getGrand(temp));
        swapColor(temp->getParent(),temp);
    } else if(getGrand(temp)->getLeft() == temp->getParent() && temp->getParent()->getLeft() == temp) {
        rightRotate(root,getGrand(temp));
        swapColor(temp->getParent(),temp);
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
    } else if(getUncle(temp) != NULL && temp->getParent()->getColor() == RED && getUncle(temp)->getColor() == RED) {
        
        temp->getParent()->setColor(BLACK);
        getUncle(temp)->setColor(BLACK);
        getGrand(temp)->setColor(RED);
        repairAdd(root,getGrand(temp));
        
      
    } else if(!getUncle(temp) || getUncle(temp) ->getColor() == BLACK)   {
        
       
      
        if(getGrand(temp)->getLeft() == getUncle(temp)) {
            
            if(temp == temp->getParent()->getLeft()) {
                
                rightRotate(root,temp->getParent());
                visualize(root,0);
                 case5(root,temp->getRight());
                return;
                
            }
            
            
            
        } else if(getGrand(temp)->getRight() == getUncle(temp)) {
            if(temp==temp->getParent()->getRight()) {
                leftRotate(root,temp->getParent());
                case5(root,temp->getLeft());
                return;
            }
        } else {
            case5(root,temp);
        }
    
      
        
    
    }
}







void add(node* &root, int value) {
    node* temp = new node(value);
    insert(root,root,temp);

    repairAdd(root,temp);
    
}

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
            /*
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
            */
        } else if(strcmp(inp, "delete") == 0) {
            char inp[100];
            cin.get(inp,100);
            cin.clear();
            cin.ignore(100,'\n');
            int a = atoi(inp);
            
            
            visualize(root,0);
            
            
        } else if(strcmp(inp, "quit") == 0) {
            running = false;
            
            
        } else {
            cout << "Enter a valid option" << endl;;
            
        }
        
        
        
        
    }
    
    
    
    
    
    
    
    
    return 0;
}




