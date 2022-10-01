#include <bits/stdc++.h>

using namespace std;

template <class T>
struct fenwick
{
    // comb function is to be replaced as required, default is sum.
    // ID is identity element of the operation.
    vector<T> bit;
    T ID = 0;
    int n;
    T comb(T a, T b) { return a + b; }
    void init(int _n)
    {
        n = _n;
        bit.assign(_n, 0);
    }
    void init(vector<T> a)
    {
        for (int i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    T sum(int r)
    {
        T ret = ID;
        for (; r >= 0; r = r & (r + 1) - 1)
            ret = comb(ret, bit[r]);
        return ret;
    }

    T sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    T add(int idx, T del)
    {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = comb(bit[idx], del);
    }
};

fenwick<int> F;

// example driver code.
int main()
{
    int n;
    // n is number of entries.
    cin >> n;

    vector<int> a(n);
    F.init(n);
    
    // take input vector.
    for (int i = 0; i<n; i++)
        cin >> a[i];

    F.init(a);

    // Use F.sum(l, r) to find sum of elements in vector from index l to r (0 - indexed).
    // Use F.add(idx, delta) to increase idx index of vector by delta.
}