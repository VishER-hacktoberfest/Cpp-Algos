#include <bits/stdc++.h>
using namespace std;

/*
This algorithm finds all occurences of pattern in text in linear time.
In this algorithm we form Z-array.
Time Complexity : O(m+n) where m is the length of string and n is length of pattern to be searched.
We make use of two functions to implement this algorithm for better understanding.
*/

// Returns Z array of the input string.
vector<int> calculate_Z(string str)
{
    vector<int> Z(str.size());
    int left = 0;
    int right = 0;
    for (int k = 1; k < str.size(); k++)
    {
        if (k > right)
        {
            left = right = k;
            while ((right < str.size()) && (str[right] == str[right - left]))
            {
                right++;
            }
            Z[k] = right - left;
            right--;
        }
        else
        {
            int k1 = k - left;
            if (Z[k1] < right - k + 1)
            {
                Z[k] = Z[k1];
            }
            else
            {
                left = k;
                while (right < str.size() && str[right] == str[right - left])
                {
                    right++;
                }
                Z[k] = right - left;
                right--;
            }
        }
    }
    return Z;
}

// Returns vector of all indices where the pattern is found.
vector<int> matchPattern(string text, string pattern)
{
    // creating a new string which will help in finding Z array.
    string newString = pattern + '$' + text;
    vector<int> result;
    vector<int> Z = calculate_Z(newString);

    // The values equal to the length of required pattern are added to the reuslt vector.
    for (int i = 0; i < Z.size(); i++)
    {
        if (Z[i] == pattern.length())
        {
            result.push_back(i - pattern.size() - 1);
        }
    }
    return result;
}

int main()
{
    string text = "aaabcxyzaaaabczaaczabbaaaaaabc";
    string pattern = "aaabc";

    vector<int> result = matchPattern(text, pattern);
    cout << "The pattern is found at positions : ";

    for (auto it : result)
    {
        cout << it << " ";
    }
    return 0;
}
