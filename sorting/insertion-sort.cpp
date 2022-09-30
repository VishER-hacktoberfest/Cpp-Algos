// C++ program that implements insertion sort

// INSERION SORT : The array is split into two parts: sorted and unsorted virtually. Each element is picked from unsorted part and placed in correct position in sorted part. 
// ( This is simiar to sorting playing cards in hands. ) 

#include <bits/stdc++.h>
using namespace std;

//Inserion sort function 
void insertionSort(int arr[], int size){
    for(int i=1; i<size; i++){
        int j = i-1, key = arr[i];

        // place the key in the corret position in arr[0..i-1] by moving the elements greater than key ahead. 
        while(key < arr[j] && j >= 0){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key; // place the key at the correct position. i.e. (j+1)th index.
    }
}

void printArray(int arr[], int size){
    for(int i=0; i<size; i++) {
        cout << arr[i] << " ";
    } 
    cout << endl;
}

int main(){
    int size;
    cout << "Enter the size of array : ";
    cin >> size;
    int arr[size];
    cout << "Enter the "<< size <<" elements of the array : "; 
    for(int i=0; i<size; i++){
        cin >> arr[i];
    }

    cout << "BEFORE SORTING : ";
    printArray(arr, size);
    insertionSort(arr, size);
    cout << "AFTER SORTING : ";
    printArray(arr,size);

    return 0;
}