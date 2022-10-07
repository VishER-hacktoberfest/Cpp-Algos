#include <bits/stdc++.h>
using namespace std;

void linear_search(int arr[], int key, int size){
    
    for (int i = 0; i < size; i++)
    {
        if(arr[i] == key){
            cout <<"found at " << i;
            return;
        }
    }
        cout << "Element not found" << endl;  
}

int main()
{
    int a;
    cout<<"enter the size of the arrray:";
    cin >> a;
    int arr[a];
    for (int i = 0; i < a; i++)
        cin >> arr[i];
        int key;
        cout<<"enter the key element:";
        cin>>key;
    linear_search(arr, key, a);
    return 0;
}
