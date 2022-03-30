/*
 Name: Hank Tsai     Lab: Heap      Instructor: Iraj Sabzevary 
 */
#include <iostream>
#include <fstream>
//Min-Heap
using namespace std; 
ifstream in ("input.txt");
void shiftUp(int * arr, int i){ //When enqueue a value
    if ( i > 0 ){  
        int parent = (i-1) / 2 ;
        if (arr[i] >= arr [parent] ){ // on the right spot
            return; 
        }
        else{ // current value is smaller than its parent
            int temp = arr [i];
            arr [i] = arr [parent];
            arr [parent] = temp;
            shiftUp(arr, parent); 
        }
    }
}
void shiftDown (int *arr, int i, int size){ //When dequeue a value
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int min = -1;
    if ( left <= size ){
        if ( left == size ){
            min = left;
        }
        else {
            if ( arr [left]< arr[right] ){
                min = left;
            }
            else{
                min = right;
            }
        }
        if ( arr [i] > arr [min] ){
            int temp = arr[i];
            arr[i] = arr [min];
            arr[min] = temp;
            shiftDown(arr, min, size); //recursive 
        }
    }
}
void printByLevel (int *arr){
    int level = 1;
    int index = 0;
    for ( int i = 1 ; i < 10 ; i *=2 ){
        cout << "Level " << level << ":  ";
        for (int j = 0 ; j < i ; j++ ){
            if ( index < 10 ){
                cout << arr[index] << "  " ;
                index++;
            }
        }
        cout << endl;
        level++;
    }
    cout<<"\n"<<endl;
}
int main(){
    int arr [10] = {};
    int temp ;
    for( int i = 0 ; i < 10 && in.good() ; i++ ){
        in >> temp;
        arr[i] = temp;
        shiftUp(arr,i);
    }
    cout << "\n\n   Initial HEAP : " << endl;
    printByLevel(arr);
    for (int i = 0 ; i < 5 ; i++ ){
        int size = 9 - i;
        cout << "       Dequeue : " << arr [0] << endl;
        arr[0] = arr [ size ];
        arr [size] = 0; 
        shiftDown(arr, 0, size-1);
        printByLevel(arr);
    }
    return 0;
}