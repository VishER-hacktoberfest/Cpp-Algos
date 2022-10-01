#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a[]={2, -4, 3, -1, 2},i;
    int local_max = 0;
    int global_max = INT_MIN;
    int n=sizeof(a)/sizeof(a[0]);
    
    for(i = 0; i < n;i++)
	{   
	    local_max = max(a[i], a[i] + local_max);
        
	    if(local_max > global_max)
	    {
	        global_max = local_max; 
	    }
	    
	}
	cout<<global_max;
	return 0;
}
