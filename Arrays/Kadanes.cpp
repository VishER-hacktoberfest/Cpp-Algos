// Kadane algorithm is used to find the maximum sum subarray in an array.
// It runs in O(n) time complexity.

// Start:
//  Initialize
//     max_sum = INT_MIN
//     sum = 0

// iterate over the array

//   (a) sum = sum + a[i]
//   (b) if(max_sum < sum)
//             max_sum = sum
//   (c) if(sum < 0)
//             sum = 0
// return max_sum
// end:

// C++ program to print largest contiguous array sum
#include <bits/stdc++.h>
using namespace std;

int maxSubArraySum(int a[], int size)
{
    int max_sum = INT_MIN, sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum = sum + a[i];
        if (max_sum < sum)
            max_sum = sum;

        if (sum < 0)
            sum = 0;
    }
    return max_sum;
}

// Driver Code
int main()
{
    int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(a) / sizeof(a[0]);

    // Function Call
    int max_sum = maxSubArraySum(a, n);
    cout << "Maximum contiguous sum is: " << max_sum;
    return 0;
}
