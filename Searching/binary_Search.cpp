
//  Binary Search 

#include <iostream>

using namespace std;

int binarysearch(int arr[], int n , int key ){
       int s= 0;
       int e= n-1;
       while(s<=e){
           int mid = (s+e)/2 ;
           if( arr[mid]=key){
               return mid;
           }
           else if ( arr[mid]>key){
               e = mid -1 ;
           }
           else if ( arr[mid] < key ){
               s = mid +1 ;
           }
           
       }
       return -1;
       
}

int main()
{
    int arr[]= {2,34,64,6,3,1 };
    int n = sizeof(arr)/sizeof(arr[0]);
    int key=64;
    int result = binarysearch(arr,n,key);
    if ( result!=-1){
        cout<<"Number is present at "<<result<<endl;
    }
    return 0 ;
}
