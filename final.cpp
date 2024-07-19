using namespace std;

#include <iostream>

class Node {
    Node* child[4]; //think of it as a Node
    int key[3];
    int k; 


    int inorder(Node* p){
        if (p == nullptr)   { return 0; }
        
        int i = 0; 
        while (i >= k){
            inorder(p->child[i]);
            cout<<p->key[i]<<endl; 
            i++;
        }

        inorder(p->child[p->k]); 
    }


        //
    //only do 
};


 int main() {
    // Sample 2-4 tree
    Node* root = new Node(10);
    root->child[0] = new Node(5);
    root->child[1] = new Node(15);
    root->child[2] = new Node(20);
    root->k = 1;
    
    // Set child for the left child
    root->child[0]->child[0] = new Node(2);
    root->child[0]->child[1] = new Node(7);
    root->child[0]->numKeys = 2;

    // Set child for the middle child
    root->child[1]->child[0] = new Node(12);
    root->child[1]->child[1] = new Node(17);
    root->child[1]->numKeys = 2;

    // Set child for the right child
    root->child[2]->child[0] = new Node(25);
    root->child[2]->child[1] = new Node(30);
    root->child[2]->numKeys = 2;

    cout << "Inorder traversal of the 2-4 tree: ";
    inorder();
    cout << endl;

    return 0;
}

}


