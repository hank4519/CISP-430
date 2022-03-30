/*
    Name: Hank Tsai ; Course: CISP 430 ; Instructor: Iraj Sabzevary 
    Lab: MergeSort with singly linked list
 */
#include <iostream>
using namespace std; 
struct Node {
    int value = -1;
    Node *next = NULL;
};
void insert (Node *& head, Node *& tail , int value) {
    if ( !head ){
        head = new Node ;
        head -> value = value;
        tail = head; 
    }
    else{ 
        Node *nn = new Node ;
        nn -> value = value ;
        tail ->next = nn;
        tail = nn ;
    }
}
void todelete (Node *&head, int de ){
    if ( head -> value == de ){
        Node * tmp = head ;
        head = head -> next; 
        delete tmp;
    }
    else{
        Node *prev = head; 
        while ( prev -> next != NULL && prev -> next -> value != de ){
            prev = prev -> next ;
        }
        Node * tmp = prev -> next;
        prev -> next = prev -> next -> next ;
        delete tmp;
    }
}
void print (Node *head){
    Node *curr = head ; 
    while ( curr ) {
        cout << curr -> value;
        if ( curr -> next ) {
            cout << " -> ";
        }
        curr = curr->next;
    }
    cout << "\n\n" << endl;
}
void split ( Node * head , Node *& left, Node *& right ){
    Node *fastptr = NULL;
    Node *slowptr = NULL;
    slowptr = head;
    fastptr = head -> next ;
    while ( !fastptr ){
        fastptr = fastptr -> next ;
        if ( !fastptr ) {
            fastptr = fastptr -> next ;
            slowptr = slowptr -> next;
        }
    }
    left = head;
    right = slowptr -> next ;
    slowptr -> next = NULL;
}
Node * merge ( Node *l, Node * r) {
    Node * res = NULL;
    if ( l == NULL ){
        return (r);
    }
    else if ( r == NULL ) {
        return (l);
    }
    if ( l -> value <= r -> value ){
        res = l ;
        res -> next = merge (l -> next , r );
    }
    else{ 
        res = r ;
        res -> next = merge ( l, r -> next );
    }
    return res;
}
Node * mergeSort (Node * head) {
    if ( head == NULL ){
        return NULL;
    }
    if ( head -> next == NULL ){
        return head ;
    }
    Node * left = NULL ;
    Node * right = NULL ;
    split ( head, left, right );
    left = mergeSort( left ) ;
    right = mergeSort( right );
    head = merge (left, right);
    return head;
}
int main(){
    Node *head = NULL;
    Node *tail = NULL;
    int a [] = { 39,49,134 ,28, 27, 19, 14, 86, 62 };
    int size = sizeof(a)/sizeof(a[0]);
    for (int i = 0 ; i < size ; i++ ){
        insert (head, tail, a [i]);
    }
    cout << "\n Merge Sort Lab \n" << endl;
    cout << "\nBefore Sorting: "; 
    print( head );
    head = mergeSort(head);
    cout << "After MergeSort: ";
    print (head);
    return 0;
}