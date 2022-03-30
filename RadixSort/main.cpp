/*
   Radix Sort Lab 
   Name: Hank Tsai ; Class: CISP 430 ; Instructor : Iraj Sabzevary 
 */ 
#include <iostream>
using namespace std;
struct Node {
    int value;
    Node *next;
};
struct Queue {
    Node * front = NULL;
    Node * rear = NULL; 
};
void enqueue ( Queue &q , int value ){
    Node * nn = new Node;
    nn -> value = value;
    nn -> next = NULL;
    if ( !q.front ){
        q.front = nn; 
        q.rear = nn;
    }
    else{
        q.rear -> next = nn;
        q.rear = nn;
    }
}
int dequeue ( Queue & q ){
    if ( q.front ){
        Node * temp = q.front;
        q.front = q.front->next;
        int num =  temp->value ;
        delete temp;
        if (!q.front){
          q.rear = q.front;  
        }
        return num;
    }
    return -1;
}
int getLength ( int num ) {
    if ( num == 0 ){
        return 1;
    }
    int digit = 0;
    while ( num != 0 ) {
        digit++;
        num /= 10; 
    }
    return digit;
}
int getMax ( int * arr, int size ){
    int max = 0; 
    for (int i = 0; i < size ; i++ ){
        int count = getLength ( arr [i] ) ;
        if ( count > max ){
            max = count;
        }
    }
    return max;
}
int size_of_queue (Queue q ){
    Queue temp = q ;
    int count = 0 ;
    while ( dequeue( q ) != -1 ) {
        count++;
    }
    q = temp;
    return count;
}
void radixSort ( int * arr , int size  ){
    Queue q [10]; 
    int maxdigit = getMax ( arr, size );
    int pow = 1 ;
    for (int i = 0; i < maxdigit ; i++ ){
        for (int j = 0 ; j < size ; j++ ){
            int index = abs(arr [j] / pow ) % 10;
            enqueue(q[index], arr[j]);
        }
        int arrIndex = 0;
        for (int i = 0 ; i < 10; i++ ){
            int count = size_of_queue(q [i] );
            for (int j = 0 ; j < count ; j++ ){
                arr [arrIndex++] = dequeue( q[i] );
            }
        }
        pow *= 10;
    }
}
int main(){
    int arr [14] = {27, 913, 8, 62, 344, 3, 14,15, 4519, 866, 11, 79, 500, 95};
    int size = sizeof(arr)/sizeof(arr[0]);
    radixSort( arr, size );
    cout << "Radix sort in Ascending Order : " << endl;
    for (auto num: arr ){
        cout << num << "  " ;
    }
    cout <<"\n" << endl;
    cout << "Radix sort in Descending Order : " << endl;
    for (int i = size-1 ; i >= 0 ;i-- ){
        cout << arr [i] << "  " ;
    }
    cout << "\n\n" << endl;
    return 0;
}