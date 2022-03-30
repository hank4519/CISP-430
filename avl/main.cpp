/*
 Name: Hank Tsai      Lab: AVL Tree      Instructor: Iraj Sabzevary 
 Completed Data: 11/11/2020
*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream in ("input.txt");
ofstream out ("output.txt");
struct Node {
    int value;
    Node *left;
    Node *right;
    int height;
};
int getBalance ( Node * node ) {
    int left = -1;
    if ( node -> left ) {
        left = node ->left->height;
    }
    int right = -1 ;
    if ( node -> right ) {
        right = node ->right->height;
    }
    return left - right;
} 
int minleft ( Node * node ){
    while ( node -> left != NULL ){
        node = node -> left ;
    }
    return node->value;
}
int getHeight (Node *node ){
    int left = -1 ;
    if ( node -> left ) {
        left = node -> left -> height ;
    }
    int right = -1 ;
    if ( node -> right ) {
        right = node -> right -> height; 
    }
    return (max (left, right) + 1) ;
}
Node* rightRotate (Node * x ) {
    Node *y = x -> left ;
    Node *z = y -> right;
    x -> left = z ;
    y -> right = x ;
    x -> height = getHeight (x);
    y -> height = getHeight (y);
    return y; 
}
Node* leftRotate (Node * x ){
    Node *y = x -> right ;
    Node *z = y -> left;
    x -> right = z ;
    y -> left = x ;
    x ->height = getHeight (x);
    y -> height = getHeight (y);
    return y;
}
Node * rebalance ( Node * node ) {
    node -> height = getHeight (node) ;
    int balance = getBalance ( node ) ;
    if ( balance == 2  && getBalance (node->left) == 1 ) { // left heavy outside 
        return rightRotate (node);
    }
    if ( balance == -2 && getBalance (node->right) == -1 ) { // right heavy outside
        return leftRotate (node);
    }
    if (balance == 2 && getBalance (node->left) == -1 ){ //left heavy inside 
        node -> left = leftRotate (node->left);
        return rightRotate (node);
    }
    if (balance == -2 && getBalance (node->right) == 1 ){ //right heavy inside 
        node -> right = rightRotate (node->right);
        return leftRotate (node);
    }
    return node; 
}
Node * insert ( Node * leaf, int val ){
    if ( !leaf ) {
        leaf = new Node;
        leaf -> left = NULL;
        leaf -> right = NULL;
        leaf -> value = val; 
        leaf -> height = 0;
        return leaf;
    }
    else if ( val < leaf -> value ) {
        leaf -> left = insert ( leaf -> left, val );
    }
    else if ( val > leaf -> value ){
        leaf -> right = insert ( leaf -> right, val );
    }
    leaf = rebalance  (leaf);
    return leaf; 
}
Node * remove ( Node * leaf, int del ) {
    if ( !leaf ) {
        return NULL;
    }
    else if ( del < leaf -> value ){
        leaf -> left = remove ( leaf -> left , del );
    }
    else if ( del > leaf -> value ) {
        leaf -> right = remove ( leaf -> right , del );
    }
    else{ //found the node to delete 
        if ( !leaf->left && !leaf->right ) { //no child
            Node *temp = leaf;
            leaf = NULL ;
            delete (temp);
            return leaf;
        }
        else if ( leaf -> left && leaf -> right ) { // two children
            int val = minleft ( leaf -> right );
            leaf -> value = val; 
            leaf -> right = remove( leaf -> right, val );
        }
        else { //One child 
            Node  *temp;
            if ( leaf -> left ){ //Only left child
                temp = leaf;
                leaf = leaf -> left ;
            }
            else{ //Only right child
                temp = leaf ;
                leaf = leaf -> right;
            }
            delete (temp);
        }
    }
    leaf = rebalance ( leaf );
    return leaf; 
}
void printEachLevel ( Node * root, int level ){
    if ( root == NULL ){
        return;
    }
    if ( level == 0 ){
        out << "  " << root -> value << "(" << root->height << ", " << getBalance (root) << ")" << "  ";
    }
    else if ( level > 0 ){
        printEachLevel (root->left, level -1);
        printEachLevel (root->right, level -1);
    }
}
void displayAVLTree (Node * root ){
    int height = root -> height;
    out << "\n  The form of each node would be: " << endl;
    out << "  node value ( height, balance factor ) \n\n" << endl;
    for (int i = 0 ; i <= height ; i++ ){
        out << "  L" << i << ":  ";
        printEachLevel (root, i );
        out << endl;
    }
    out << "\n\n\n\n\n\n" << endl;
}
int main(){
    Node *root = NULL;
    int temp;
    while (in.good()) {
        in>>temp;
        root = insert (root, temp);
    }
    displayAVLTree(root);
    return 0;
}