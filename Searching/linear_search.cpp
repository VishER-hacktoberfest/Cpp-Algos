#include <bits/stdc++.h>
using namespace std;

void linear_search(int arr[], int num, int size){
    int pos, fl = 0;
    for (int i = 0; i < size; i++)
    {
        if(arr[i] == num){
            cout << i+1 << endl;
            fl = 1;
        }
    }
    if(fl == 0)
        cout << "Element not found" << endl;  
}

int main()
{
    int a;
    cin >> a;
    int arr[a];
    for (int i = 0; i < a; i++)
        cin >> arr[i];
    linear_search(arr, 2, a);
    return 0;
}
