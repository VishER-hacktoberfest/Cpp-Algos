#include <iostream>
using namespace std;

int binarysearch(int arr[], int n, int k){
        // code here
        int left = 0; int right = n-1;
        while(left <= right){
            int mid = (left + right)/2;
            if(arr[mid] == k){
                return mid;
            }
            else if(arr[mid] < k){
                left = mid+1;
            }
            else{
                right = mid-1;
            }
        }
        return -1;
}

int main() {
    
    int arr[] = {12, 13, 25, 30, 35, 36};
    int N = 6;  //Size of the array
    int key = 35; // the value which you want to find in array
    int found = binarysearch(arr,N,key); // call fun.
    if(found != -1){
        cout<<"Key value is found at index : "<<found<<endl;
    }
    else{
        cout<<"Key value is not present in array"<<endl;
    }
    
	return 0;
}
