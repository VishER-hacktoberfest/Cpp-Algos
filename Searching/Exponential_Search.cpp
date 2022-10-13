#include <iostream>
using namespace std;

int binarySearch(int arr[], int a, int b, int x)
{
    while (a <= b) {
        int m = a + (b - a) / 2;
        if (arr[m] == x)
            return m;
        if (arr[m] < x)
            a = m + 1;
        else
            b = m - 1;
    }
    return -1;
}

int exponentialSearch(int arr[], int n, int x)
{
    if (arr[0] == x)
        return 0;
    int i = 1;
    while (i < n && arr[i] <= x)
        i = i * 2;

    return binarySearch(arr, i / 2,
                        min(i, n - 1), x);
}

int main()
{
    int n = 11;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int x = 10;
    int result = exponentialSearch(arr, n, x);
    if (result == -1) {
        cout << "Element not found !!";
    }
    else cout << "Element found at index " << result;
    return 0;
}