/*
Postfix Evaluation Lab
Name: Hank Tsai; Course: CISP 430; Instructor: Iraj Sabzevary
 */
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ifstream in ("input.txt") ;
ofstream out ("output.txt");

struct Node {
    int value;
    Node *next; 
};
Node* push ( Node* top , int value ) {
        Node *nn = new Node;
        nn -> value = value ;
        nn -> next = top;
        return nn;
}
int pop ( Node *&top ){
    if ( top ){
        int val = top -> value;
        Node *tmp = top;
        top = top ->next;
        delete tmp;
        return val;
    }
    return -1;
}
int main(){
    char collection [30];
    while ( in.good() ){
        in >> collection;
    }
    Node *stack;
    int res;
    for (size_t i = 0; i < strlen(collection); i++ ){
        if ( collection [i] == '+' ){
            res = pop(stack) + pop(stack);
            stack = push (stack, res);
        }
        else if ( collection [i] == '-' ){
            int t = pop(stack);
            int b = pop(stack);
            stack = push(stack,b-t);
        }
        else if ( collection [i] == '*' ){
            res = pop(stack) * pop(stack);
            stack = push (stack, res);
        }
        else if ( collection [i] == '/'){
            int t = pop (stack);
            int b = pop(stack);
            stack = push(stack,b/t);
        }
        else {
            stack = push(stack, collection[i] - '0');
        }
    }
    out << pop(stack) <<endl;
    cout << "\nAnswer for the postfix evaluation has been written into output.txt file. \n\n" << endl;
    in.close();
    out.close();
    return 0;
}