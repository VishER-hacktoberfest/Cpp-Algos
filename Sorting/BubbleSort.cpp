#include<iostream>
using namespace std;
int main()
{
    int n, i, arr[50], j, temp;
    //Taking input from user 
    cout<<"Enter the Size (max. 50): ";
    cin>>n;
    cout<<"Enter "<<n<<" Numbers: ";
    for(i=0; i<n; i++)
        cin>>arr[i];

    cout<<endl;
    //the algorithm starts from here->
    for(i=0; i<(n-1); i++)
    //outer loop
    {
        for(j=0; j<(n-i-1); j++)
        //inner loop
        {
            if(arr[j]>arr[j+1])
            {
                //swapping
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }

        }
    }
    cout<<"The New Array is:  ";
    cout<<endl;
    //Printing the array
    for(i=0; i<n; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}