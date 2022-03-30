/*  Doubly Linked List Lab
 * Name: Hank Tsai    Course: CISP 430     Instructor: Iraj Sabzevary 
 */
#include <iostream>
#include <fstream>
#include <string> 
using namespace std;
ifstream in ("input.txt");
ofstream out ("output.txt");
struct Node {
    string name = "";
    Node *prev = NULL;
    Node *next = NULL;
};
void insert (Node *&head, Node *& tail, string n){
    if ( !head ) {
        head = new Node;
        tail = head;
        head -> name = n;
        tail -> name = n;
    }
    else if ( n < head -> name ){
        Node *nn = new Node;
        nn -> name = n;
        nn -> next = head;
        head -> prev = nn;
        head = nn ;
    }
    else if  ( n > tail -> name ){
        Node * nn = new Node; 
        nn -> name = n ;
        nn -> prev = tail ;
        tail -> next = nn;
        tail = nn;
    }
    else {
        Node * curr = head;
        while ( n > curr -> name ){
            curr = curr->next;
        }
        Node * nn = new Node ;
        nn -> name = n ;
        curr -> prev -> next = nn;
        nn -> prev = curr -> prev ;
        nn -> next = curr;
        curr ->prev = nn; 
    }
}  
void deletion ( Node *& head, Node *&tail , string n ){
    Node * curr =  head;
    while ( curr ){
        if ( curr->name == n ){
            break; 
        }
        curr = curr ->next;
    }
    if ( curr ){ // if the string is found
        if (curr->prev) { // Has previous node
            curr -> prev -> next = curr -> next;
        }
        else{ // head node
            head = curr ->next;
        }
        if (curr -> next) { //Has next node
            curr -> next -> prev = curr -> prev;
        }
        else { //tail node
            tail = curr -> prev;
        }
        delete curr;
    }
}
void printAscending (Node *& head ){
    Node * curr = head;
    cout << "Ascending order: " << endl;
    out << "Ascending order: " << endl;
    while ( curr ){
        cout << curr -> name << endl;
        out << curr -> name << endl;
        curr = curr->next;
    }
}
void printDescending (Node *& tail){
    Node *curr = tail; 
    cout << "Descending order: " << endl;
    out << "Descending order : " << endl;
    while ( curr ){
        cout << curr -> name << endl;
        out << curr -> name << endl;
        curr = curr -> prev;
    }
}
int main(){
    Node *head = NULL;
    Node *tail = NULL; 
    string tmp;
    string name_to_delete;
    while (in.good()){
        in >> tmp; 
        if ( tmp == "delete" ){
            in >> name_to_delete;
            deletion (head, tail, name_to_delete);
        }
        else{
            insert (head, tail, tmp);
        }
    }
    printAscending(head);
    cout << "===============================\n" << endl;
    out << "\n##############################\n" << endl;
    printDescending(tail);
    cout << "\nContents have also been written to the file output.txt  \n\n" << endl;
    delete head;
    delete tail;
    in.close();
    out.close();
    return 0;
}