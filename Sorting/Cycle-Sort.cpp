#include <iostream>
using namespace std;

/*
Cycle sort is an algorithm is used to sort an array in minimum writes.
Time Complexity : O(n^2)
*/

// Function to implement Cycle Sort
void cycleSort(int a[], int n)
{
    int writes = 0;
    for (int c_start = 0; c_start <= n - 2; c_start++)
    {
        int item = a[c_start];
        int pos = c_start;

        // determining the correct position of the element from number of elements less than it.
        for (int i = c_start + 1; i < n; i++)

            if (a[i] < item)
                pos++;
        // Condition to check if element is already in the correct position.
        if (pos == c_start)
            continue;
        // Condition to ensure we don't swap equal elements.
        while (item == a[pos])
            pos += 1;
        if (pos != c_start)
        {
            swap(item, a[pos]);
            writes++;
        }
        while (pos != c_start)
        {
            pos = c_start;
            for (int i = c_start + 1; i < n; i++)
                if (a[i] < item)
                    pos += 1;
            while (item == a[pos])
                pos += 1;
            if (item != a[pos])
            {
                swap(item, a[pos]);
                writes++;
            }
        }
    }
}
int main()
{
    int a[] = {11, 12, 16, 13, 11, 11, 14, 12, 15};
    int n = 9;
    cycleSort(a, n);
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    return 0;
}