   public:
    #define ll long long
    // arr: input array
    // n: size of array
    //Function to find the sum of contiguous subarray with maximum sum.
    ll maxSubarraySum(int arr[], int n){
        
        // Your code here
    ll maxi = INT_MIN;
    ll sum = 0;
    
    for(int i=0; i<n; i++)
    {
        sum = sum + arr[i];
        maxi = max(sum, maxi);
        if(sum < 0){
            sum = 0;}
    }
        
     return maxi;   
    }
};
