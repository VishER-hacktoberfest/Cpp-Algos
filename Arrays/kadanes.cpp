#include <bits/stdc++.h>
using namespace std;
int getMaxSubarray(int a[],int n){
	int ans=INT_MIN;
	int sum=0;
	for(int i=0;i<n;i++){
		sum=sum+a[i];
		ans=max(ans,sum);
		if(sum<0){
			sum=0;
		}
	}
	//return the ans
	return ans;
}
int main()
{
    int a[]={2, -4, 3, -1, 2},i;
    int local_max = 0;
    int global_max = INT_MIN;
    int n=sizeof(a)/sizeof(a[0]);
	cout<<getMaxSubarray(a,n);
    
}
